//! \brief Marketplace Provider
//! \file MaketProvider.hpp
//!
//! A marketplace provider is a marketplace where goods can be sold by sellers.
//! A marketplace facilitates a sale and takes a commision.  Marketplace providers
//! may or may not collect sales taxes.
//!
//! \copyright
//! Copyright (C) 2025 Joe Turner; all rights reserved.
#ifndef _MARKETPROVIDER_HPP_
#define _MARKETPROVIDER_HPP_

//! \brief Marketplace Provider
//!
//! As defined by state tax agencies, a marketplace provider facilitates sales and 
//! may or may not collect and remit sales tax on sales to the various states.
//! A marketplace provider is a marketplace where goods can be sold by sellers.
//! A marketplace facilitates a sale and takes a commision.  Marketplace providers
//! may or may not collect sales taxes.
//!
//! If a state sales tax agency requires a marketplace provider to collect and remit sales tax,
//! the marketplace provider is responsible for collecting and remitting sales tax
//! on behalf of the seller.  This complicates sales and use tax compliance for sellers.
enum MARKETPLACE_PROVIDER
{

    //! \brief Amazon marketplace provider
    MARKETPLACE_AMAZON_SELLER,    

    //! \brief eBay marketplace provider
    //! eBay marketplace collects sales tax on behalf of sellers and remits
    //! taxes to states; has ebay API for sales information.
    //!
    MARKETPLACE_EBAY,

    //! \brief Poshmark marketplace provider
    //!
    //! Poshmark collects sales tax on a limited number of states nd remits to state tax agencies.
    //! No API.
    MARKETPLACE_POSHMARK,
};

#endif
