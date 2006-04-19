
/*
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005, 2006 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qla/config.hpp>
#endif
#include <qla/basketoption.hpp>
#include <qla/typefactory.hpp>
#include <qla/generalutils.hpp>

namespace QuantLibAddin {

    BasketOption::BasketOption(
            const std::string &handleBlackScholes,
            const std::string &basketID,
            const std::string &optionTypeID,
            const double &strike,
            const std::string &exerciseID,
            const long &exerciseDate,
            const long &settlementDate,
            const std::string &engineID,
            const long &timeSteps) {

        QuantLib::BasketOption::BasketType basketType = 
            Create<QuantLib::BasketOption::BasketType>()(basketID);
        QuantLib::Option::Type type = 
            Create<QuantLib::Option::Type>()(optionTypeID);

        boost::shared_ptr<QuantLib::PlainVanillaPayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike));
        boost::shared_ptr<QuantLib::Exercise> exercise = 
            Create<boost::shared_ptr<QuantLib::Exercise> >()(exerciseID, exerciseDate, settlementDate);
        boost::shared_ptr<QuantLib::PricingEngine> pricingEngine =
            Create<boost::shared_ptr<QuantLib::PricingEngine> >()(engineID, timeSteps);

        OH_GET_REFERENCE(blackScholesProcess, handleBlackScholes,
            GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)
        boost::shared_ptr<QuantLib::StochasticProcess> stochasticProcess=
            boost::dynamic_pointer_cast<QuantLib::StochasticProcess>
            (blackScholesProcess);

        mInstrument = boost::shared_ptr<QuantLib::BasketOption>(
            new QuantLib::BasketOption(
                basketType,
                stochasticProcess, 
                payoff, 
                exercise, 
                pricingEngine));
    }

}

