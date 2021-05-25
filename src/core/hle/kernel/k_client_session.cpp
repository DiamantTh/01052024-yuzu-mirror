// Copyright 2021 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/kernel/hle_ipc.h"
#include "core/hle/kernel/k_client_session.h"
#include "core/hle/kernel/k_server_session.h"
#include "core/hle/kernel/k_session.h"
#include "core/hle/kernel/k_thread.h"
#include "core/hle/kernel/svc_results.h"
#include "core/hle/result.h"

namespace Kernel {

KClientSession::KClientSession(KernelCore& kernel_)
    : KAutoObjectWithSlabHeapAndContainer{kernel_} {}
KClientSession::~KClientSession() = default;

void KClientSession::Destroy() {
    parent->OnClientClosed();
    parent->Close();
}

void KClientSession::OnServerClosed() {}

ResultCode KClientSession::SendSyncRequest(KThread* thread, Core::Memory::Memory& memory,
                                           Core::Timing::CoreTiming& core_timing) {
    // Signal the server session that new data is available
    return parent->GetServerSession().HandleSyncRequest(thread, memory, core_timing);
}

} // namespace Kernel