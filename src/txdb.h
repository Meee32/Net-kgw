// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_TXDB_H
#define BITCOIN_TXDB_H

#define DATABASE_VERSION 2
#endif  // BITCOIN_TXDB_H
#include "db.h"
#include <stdint.h>
/** Access to the transaction database (blkindex.dat) */

class CTxDB : public CDB
{
public:
    CTxDB(const char* pszMode="r+") : CDB("blkindex.dat", pszMode) { }
private:
    CTxDB(const CTxDB&);
    void operator=(const CTxDB&);
public:
    bool ReadTxIndex(uint256 hash, CTxIndex& txindex);
    bool UpdateTxIndex(uint256 hash, const CTxIndex& txindex);
    bool AddTxIndex(const CTransaction& tx, const CDiskTxPos& pos, int nHeight);
    bool EraseTxIndex(const CTransaction& tx);
    bool ContainsTx(uint256 hash);
    bool ReadDiskTx(uint256 hash, CTransaction& tx, CTxIndex& txindex);
    bool ReadDiskTx(uint256 hash, CTransaction& tx);
    bool ReadDiskTx(COutPoint outpoint, CTransaction& tx, CTxIndex& txindex);
    bool ReadDiskTx(COutPoint outpoint, CTransaction& tx);
    bool WriteBlockIndex(const CDiskBlockIndex& blockindex);
    bool ReadHashBestChain(uint256& hashBestChain);
    bool WriteHashBestChain(uint256 hashBestChain);
    bool ReadBestInvalidTrust(CBigNum& bnBestInvalidTrust);
    bool WriteBestInvalidTrust(CBigNum bnBestInvalidTrust);

    bool ReadBestInvalidTrust(uint256& nBestInvalidTrust)
    {
        CBigNum bn;
        if (ReadBestInvalidTrust(bn)) {
            nBestInvalidTrust=bn.getuint256();
            return true;
        }
        else
            return false;
    }


    bool WriteBestInvalidTrust(uint256 nBestInvalidTrust){return WriteBestInvalidTrust(CBigNum(nBestInvalidTrust));}

    bool ReadSyncCheckpoint(uint256& hashCheckpoint);
    bool WriteSyncCheckpoint(uint256 hashCheckpoint);
    bool ReadCheckpointPubKey(std::string& strPubKey);
    bool WriteCheckpointPubKey(const std::string& strPubKey);

    bool LoadBlockIndex();
private:
    bool LoadBlockIndexGuts();
};
