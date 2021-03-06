/**
 * \file dcs/des/min_estimator.hpp
 *
 * \brief Minimum estimator for independent and identically distributed samples.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_DES_MIN_ESTIMATOR_HPP
#define DCS_DES_MIN_ESTIMATOR_HPP


#include <cmath>
#include <cstdlib>
#include <dcs/debug.hpp>
#include <dcs/des/base_statistic.hpp>
#include <dcs/des/statistic_categories.hpp>
#include <dcs/math/constants.hpp>
#include <dcs/math/stats/distribution/students_t.hpp>
#include <dcs/math/stats/function/quantile.hpp>
#include <string>


namespace dcs { namespace des {

/**
 * \brief Minimum estimator for independent and identically distributed samples.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ValueT, typename UIntT>
class min_estimator: public base_statistic<ValueT,UIntT>
{
	private: typedef base_statistic<ValueT,UIntT> base_type;
	public: typedef ValueT value_type;
	public: typedef UIntT uint_type;
	public: typedef min_statistic_category category_type;


	public: explicit min_estimator(value_type ci_level=base_type::default_confidence_level)
	: count_(0),
	  m_(::dcs::math::constants::infinity<value_type>::value),
	  ci_level_(ci_level)
	{
		// Empty
	}


	private: statistic_category do_category() const
	{
		return min_statistic;
	}


	private: void do_collect(value_type obs, value_type /*ignored_weight*/)
	{
		++count_;

		if (m_ > obs)
		{
			m_ = obs;
		}
	}


	private: value_type do_confidence_level() const
	{
		return ci_level_;
	}


	private: value_type do_estimate() const
	{
		return m_;
	}


	private: value_type do_half_width() const
	{
		return 0;
	}


	private: uint_type do_num_observations() const
	{
		return count_;
	}


	private: value_type do_relative_precision() const
	{
		return 0;
	}


	private: void do_reset()
	{
		m_ = ::dcs::math::constants::infinity<value_type>::value;
		count_ = uint_type(0);
	}


	private: value_type do_variance() const
	{
		return 0;
	}


	private: ::std::string do_name() const
	{
		return "Min";
	}


	/// Number of observations seen to date.
	private: uint_type count_;
	/// Accumulator for the minimum value.
	private: value_type m_;
	/// Confidence level for interval estimation.
	private: value_type ci_level_;
};


}} // Namespace dcs::des


#endif // DCS_DES_MIN_ESTIMATOR_HPP
