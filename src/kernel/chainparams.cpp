// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Hashvive developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kernel/chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/amount.h>
#include <consensus/merkle.h>
#include <consensus/params.h>
#include <hash.h>
#include <kernel/messagestartchars.h>
#include <logging.h>
#include <primitives/block.h>
#include <primitives/transaction.h>
#include <script/interpreter.h>
#include <script/script.h>
#include <uint256.h>
#include <util/chaintype.h>
#include <util/strencodings.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>

using namespace util::hex_literals;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.version = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Hashvive nasceu hoje!"; // Mensagem personalizada
    const CScript genesisOutputScript = CScript() << "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"_hex << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

// Main Network
class CMainParams : public CChainParams {
public:
    CMainParams() {
        m_chain_type = ChainType::MAIN;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // 2 semanas
        consensus.nPowTargetSpacing = 300; // 5 minutos
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% de 2016
        consensus.nMinerConfirmationWindow = 2016;
        consensus.defaultAssumeValid = uint256S("0x00");

        genesis = CreateGenesisBlock(1736391250, 2083236893, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")); // Substitua pelo hash correto
        assert(genesis.hashMerkleRoot == uint256S("96fb97a45f46a11eb4059325cd5c834186eb35eda1b78021bab19b249578fa50"));     // Substitua pelo Merkle root correto

        vSeeds.emplace_back("127.0.0.1"); // Adicione seus seeds aqui

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48); // Endereços começam com 'H'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 50);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 176);

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_main), std::end(chainparams_seed_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")}, // Checkpoint para o bloco gênesis
            }
        };

        chainTxData = ChainTxData{
            1736391250, // Timestamp do bloco gênesis
            0,          // Transações no bloco gênesis
            0           // Taxa de transações
        };
    }
};

// Test Network
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        m_chain_type = ChainType::TESTNET;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // 2 semanas
        consensus.nPowTargetSpacing = 300; // 5 minutos
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% para testnet
        consensus.nMinerConfirmationWindow = 2016;

        genesis = CreateGenesisBlock(1736391250, 2083236893, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")); // Substitua pelo hash correto
        assert(genesis.hashMerkleRoot == uint256S("96fb97a45f46a11eb4059325cd5c834186eb35eda1b78021bab19b249578fa50"));     // Substitua pelo Merkle root correto

        vSeeds.emplace_back("testnet-seed.hashvive.org");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111); // Prefixo para Testnet
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")}, // Checkpoint para o bloco gênesis
            }
        };

        chainTxData = ChainTxData{
            1736391250,
            0,
            0
        };
    }
};

// Regression Test Network
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        m_chain_type = ChainType::REGTEST;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // 2 semanas
        consensus.nPowTargetSpacing = 300; // 5 minutos
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        genesis = CreateGenesisBlock(1736391250, 2, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")); // Substitua pelo hash correto
        assert(genesis.hashMerkleRoot == uint256S("<insira_merkle_root>"));     // Substitua pelo Merkle root correto

        vSeeds.clear(); // Regtest não usa seeds

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0000000076798936e23559c7cf6cb7a5175331047889b155496a2bbd4c94e900")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
    }
};

std::unique_ptr<const CChainParams> CChainParams::Main() {
    return std::make_unique<CMainParams>();
}

std::unique_ptr<const CChainParams> CChainParams::TestNet() {
    return std::make_unique<CTestNetParams>();
}

std::unique_ptr<const CChainParams> CChainParams::RegTest() {
    return std::make_unique<CRegTestParams>();
}
