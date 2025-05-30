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
    if (blockHeight >= 823500) {
        founderAddress = "BrfdituY8Y6hG914K2t5hxEcrjjbfvsQce";
    } else {
        founderAddress = DEFAULT_FOUNDER_ADDRESS;
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

bool FounderPayment::IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward) {
    UpdateFounderAddressForHeight(height);

    CScript payee = GetScriptForDestination(DecodeDestination(founderAddress));
    const CAmount founderReward = getFounderPaymentAmount(height, blockReward);
    BOOST_FOREACH(const CTxOut& out, txNew.vout) {
        if (out.scriptPubKey == payee && out.nValue >= founderReward) {
            return true;
        }
    }

    return false;
}
