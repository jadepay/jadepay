// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The Jadepay developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <stdio.h> //
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"



/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof (ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,  uint256("0x0000071d877e71cdd4072a6fca7e2fece5d6c902ba33671a83e658299a2c1b3c"))
        
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1533097800, // * UNIX timestamp of last checkpoint block
    1, // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    800 // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of
        ( 0,  uint256("0x000002163d875acf11fa454873a0ae337abf56f08574971d7ab7be06aa062469"))
        
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1530940000,
    0,
    0
};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x000002163d875acf11fa454873a0ae337abf56f08574971d7ab7be06aa062469"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1530940000,
    0,
    0
};

class CMainParams : public CChainParams {
public:

    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xda;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("04e7635d1cac6db47309ea4fcc3d846258fbbff3944f56f1fd1ff89e93f2edf691d10de3fc58e01fa3f0463e4fa1d2cfd2ca036cdef074050329eb965c3017eb45");
        nDefaultPort = 22155;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Jadepay starting difficulty is 1 / 2^12 
        nSubsidyHalvingInterval = 2100000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 3 * 60; // Jadepay: 3 minute
        nTargetSpacing = 3 * 60; // Jadepay: 3 minute
        nLastPOWBlock = 2000000;
	nMaxMoneyOut = 25000000 * COIN;
        nMaturity = 100;
        nModifierUpdateBlock = 1;
        const char* pszTimestamp = "Challenger approaching Never gonna give up";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*) pszTimestamp, (const unsigned char*) pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0484d7b993acfc9686b20dabeb4d8acfe8cc2c0bdab119fc141a1a56581115f3f8fd9e6aaf4141d189a9fc8814585999bf47cfa0fb56340dccf3cbffc6e0cf394e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1533097800;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 105162;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000071d877e71cdd4072a6fca7e2fece5d6c902ba33671a83e658299a2c1b3c"));
        assert(genesis.hashMerkleRoot == uint256("0x63482500d4814d581d1d485a3c9e70399c72e496c79ec437b20223ec21b87b30"));

        vSeeds.push_back(CDNSSeedData("node01.jadepay.org", "node01.jadepay.org"));
        vSeeds.push_back(CDNSSeedData("explorer.jadepay.org", "explorer.jadepay.org"));
        vSeeds.push_back(CDNSSeedData("91.214.117.26", "91.214.117.26.org"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43); // Jadepay address start with J
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is '217'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xd9).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "04e125f52309d61d353c50914435c52c18a0b0c06cf770da68e11e8a5f440629e7e0b95de70b117aff78e3bae9727cec786c9e719bb8be098aab9d35f6c81c61fa";
        strObfuscationPoolDummyAddress = "JbujKSjAsPhFUEq4vz4RKd4Mb43EQW5Awu";
        nStartMasternodePayments = 1533186000; //(GMT): Thursday, August 2, 2018 5:00:00 AM
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:

    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x1e;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04e7635d1cac6db47309ea4fcc3d846258fbbff3944f56f1fd1ff89e93f2edf691d10de3fc58e01fa3f0463e4fa1d2cfd2ca036cdef074050329eb965c3017eb45");
        nDefaultPort = 12155;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Jadepay: 1 day
        nTargetSpacing = 1 * 60; // Jadepay: 1 minute
        nLastPOWBlock = 12000;
	nMaxMoneyOut = 200000 * COIN;
        nMaturity = 10;
        genesis.nTime = 1530940000;
        genesis.nNonce = 2157120;
        hashGenesisBlock = genesis.GetHash();

        genesis.nBits = bnProofOfWorkLimit.GetCompact();

        hashGenesisBlock == uint256("0x000002163d875acf11fa454873a0ae337abf56f08574971d7ab7be06aa062469");
        genesis.hashMerkleRoot == uint256("0x63482500d4814d581d1d485a3c9e70399c72e496c79ec437b20223ec21b87b30");

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("test.jadepay.org", "test.jadepay.org"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet jadepay addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet jadepay script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet jadepay BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet jadepay BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet jadepay BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04e125f52309d61d353c50914435c52c18a0b0c06cf770da68e11e8a5f440629e7e0b95de70b117aff78e3bae9727cec786c9e719bb8be098aab9d35f6c81c61fa";
        strObfuscationPoolDummyAddress = "TUQ57Fbh1crybrDhV6X9SDH95H4oSq4v6p";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:

    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Jadepay: 1 day
        nTargetSpacing = 1 * 60; // Jadepay: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31923;
        //assert(hashGenesisBlock == uint256("0x"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:

    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 41923;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases

    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) {
        nSubsidyHalvingInterval = anSubsidyHalvingInterval;
    }

    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) {
        fDefaultConsistencyChecks = afDefaultConsistencyChecks;
    }

    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {
        fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks;
    }

    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) {
        fSkipProofOfWorkCheck = afSkipProofOfWorkCheck;
    }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams() {
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
