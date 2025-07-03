// founder_payment.cpp

#include <founder_payment.h>
#include <rpc/server.h>
#include <util.h>
#include <chainparams.h>
#include <boost/foreach.hpp>
#include <key_io.h>

CAmount FounderPayment::getFounderPaymentAmount(int blockHeight, CAmount blockReward) {
    if (blockHeight <= startBlock) {
        return 0;
    }
    for (int i = 0; i < rewardStructures.size(); i++) {
        FounderRewardStructure rewardStructure = rewardStructures[i];
        if (rewardStructure.blockHeight == INT_MAX || blockHeight <= rewardStructure.blockHeight) {
            return blockReward * rewardStructure.rewardPercentage / 100;
        }
    }
    return 0;
}

void FounderPayment::UpdateFounderAddressForHeight(int blockHeight) {
    if (blockHeight > 834000) {
        founderAddress = DEFAULT_FOUNDER_ADDRESS;
    } else {
        founderAddress = "BanxgMPcMpXnuWQ2ogfQqEkwwVtjhAhXBR";
    }
}

void FounderPayment::FillFounderPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutFounderRet) {
    UpdateFounderAddressForHeight(nBlockHeight);

    CAmount founderPayment = getFounderPaymentAmount(nBlockHeight, blockReward);
    txoutFounderRet = CTxOut();

    CTxDestination founderAddr = DecodeDestination(founderAddress);
    if (!IsValidDestination(founderAddr)) {
        throw JSONRPCError(RPC_INVALID_ADDRESS_OR_KEY, strprintf("Invalid Bitoreum Founder Address: %s", founderAddress.c_str()));
    }

    CScript payee = GetScriptForDestination(founderAddr);

    txNew.vout[0].nValue -= founderPayment;
    txoutFounderRet = CTxOut(founderPayment, payee);
    txNew.vout.push_back(txoutFounderRet);

    LogPrintf("FounderPayment::FillFounderPayment -- Founder payment %lld to %s\n", founderPayment, founderAddress.c_str());
}

// this is called with nHeight - 1 always
bool FounderPayment::IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward) {
    bool skipPayeeCheck = false;
    // technically since 834000 - 834600 will be ignored (payments to both new and old addresses, we can just
    if ((height > 834000-1) && (height < 834600-1)) {
        LogPrintf("FounderPayment::IsBlockPayeeValid -- payee check disabled for height %d\n", height);
        skipPayeeCheck = true;
    }

    UpdateFounderAddressForHeight(height);

    CScript payee = GetScriptForDestination(DecodeDestination(founderAddress));
    const CAmount founderReward = getFounderPaymentAmount(height, blockReward);
    BOOST_FOREACH(const CTxOut& out, txNew.vout) {
        if ((out.scriptPubKey == payee || skipPayeeCheck) && out.nValue >= founderReward) {
            return true;
        }
    }

    return false;
}