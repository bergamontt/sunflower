#pragma once

#include <QString>
#include <QStringList>
#include <QTemporaryFile>

#include <memory>

namespace sun::monitor::wayland::utils
{
    std::unique_ptr<QTemporaryFile> createScript(const QString& path, const QStringList& args);
    int loadScript(const QString& path, const QString& name);
    void runScript(int scriptId);
    void stopScript(int scriptId);
    void unloadScript(const QString& name);
    void executeScript(const QString& path, const QString& name, const QStringList& args);
} // sun::monitor::wayland