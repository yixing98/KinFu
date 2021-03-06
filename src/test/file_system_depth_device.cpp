#include <kinfu/file_system_depth_device.hpp>


#include <Eigen/Dense>
#include <kinfu/filesystem.hpp>
#include <kinfu/path.hpp>
#include <cstddef>
#include <utility>
#include <vector>
#include <catch.hpp>


SCENARIO("file_system_depth_device loads depth information from files in the file system", "[kinfu][depth_device][file_system_depth_device]") {
	
	GIVEN("A file_system_depth_device") {
		
		class mock_factory : public kinfu::file_system_depth_device_frame_factory {
			
			
			private:
			
			
				std::size_t num_;
			
			
			public:
			
			
				mock_factory () noexcept : num_(0) {	}
				
				
				virtual value_type operator () (const kinfu::filesystem::path &, value_type v) override {
					
					++num_;
					return v;
					
				}
				
				
				virtual std::size_t width () const noexcept override {
					
					return 0;
					
				}
				
				
				virtual std::size_t height () const noexcept override {
					
					return 0;
					
				}
				
				
				virtual Eigen::Matrix3f k () const noexcept override {
					
					return Eigen::Matrix3f::Zero();
					
				}
				
				
				std::size_t get () const noexcept {
					
					return num_;
					
				}
			
			
		};
		
		kinfu::filesystem::path fake_path(kinfu::current_executable_parent_path());
		fake_path/="..";
		fake_path/="data/test/file_system_depth_device";
		mock_factory fac;
		kinfu::file_system_depth_device fsdd(std::move(fake_path),fac);
		
		THEN("operator bool returs true") {
			
			CHECK(fsdd);
			
		}
		
		WHEN("It is invoked") {
			
			auto frame=fsdd();
			
			THEN("The underlying factory is invoked exactly once") {
				
				CHECK(fac.get()==1U);
				
			}
			
			THEN("Invoking it again throws an exception as there are no more files") {
				
				CHECK_THROWS_AS(fsdd(),kinfu::file_system_depth_device::end);
				
			}
			
			THEN("operator bool returns false as there are no more files") {
				
				CHECK(!fsdd);
				
			}
			
		}
	
	}
	
	
}
