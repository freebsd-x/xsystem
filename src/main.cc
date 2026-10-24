#include "xserver/system_service.h"
#include "shared/protocol.h"
#include "shared/logger.h"
#include "xserver/crash_handler.h"
#include <csignal>
#include <unistd.h>
#include <atomic>

static std::atomic<bool> g_running{true};

static void signal_handler(int) {
    g_running = false;
}

int main() {
    fbx::shared::Logger::init("xsystem");
    fbx::xserver::installCrashHandler("xsystem");
    LOG_INFO("xsystem starting...");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    LOG_INFO("SystemService running. Waiting for SIGTERM/SIGINT.");

    // SystemService provides CPU/memory/battery stats via XBus.
    // The IPC socket is managed by the compositor; this daemon is a
    // placeholder for running SystemService as a standalone process.
    while (g_running) {
        pause();
    }

    LOG_INFO("xsystem shutting down.");
    return 0;
}
