/**
 *	\file
 */


#pragma once

#include <dynfu/pose_estimation_pipeline_block.hpp>
#include <cstddef>


namespace dynfu {
	
	
	/**
	 *	An implementation of a \ref pose_estimation_pipeline_block
	 *	that uses the Eigen math library to calculate a new sensor
	 *	pose estimation.
	 *
	 *	\sa kinect_fusion
	 */
	class kinect_fusion_eigen_pose_estimation_pipeline_block: public pose_estimation_pipeline_block {

		private:
			float epsilon_d_;
			float epsilon_theta_;
			std::size_t frame_width_;
			std::size_t frame_height_;
			std::size_t numit_;

			Eigen::Matrix4f iterate(
				measurement_pipeline_block::vertex_value_type::element_type &,
				measurement_pipeline_block::normal_value_type::element_type &,
				surface_prediction_pipeline_block::vertex_value_type::element_type *,
				surface_prediction_pipeline_block::normal_value_type::element_type *,
				Eigen::Matrix3f,
				Eigen::Matrix4f,
				Eigen::Matrix4f
			);

		public:

			/**
			 *  Creates a new kinect_fusion_eigen_pose_estimation_pipeline_block.
			 * 
			 *  \param [in] epsilon_d
			 *      The rejection distance in Equation 17, \f$\epsilon_d\f$
			 *
			 *  \param [in] epsilon_theta
			 *      The normal rejection angle in Equation 17, \f$\epsilon_\theta\f$
			 *
			 *  \param [in] frame_width
			 *      The width of the depth frame
			 *
			 *  \param [in] frame_height
			 *      The height of the depth frame
			 *
			 *  \param [in] numit
			 *      The number of iterations to use
			 *
			 */
			kinect_fusion_eigen_pose_estimation_pipeline_block (
				float epsilon_d,
				float epsilon_theta,
				std::size_t frame_width,
				std::size_t frame_height,
				std::size_t numit=15
			);

			virtual value_type operator () (
				measurement_pipeline_block::vertex_value_type::element_type & v,
				measurement_pipeline_block::normal_value_type::element_type & n,
				surface_prediction_pipeline_block::vertex_value_type::element_type * prev_v,
				surface_prediction_pipeline_block::normal_value_type::element_type * prev_n,
				Eigen::Matrix3f k,
				value_type t_gk_minus_one
			) override;


	};

	
}
