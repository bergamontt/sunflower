#include "kdewayland/kwinscriptutils.h"

#include <QFile>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

namespace sun::monitor::wayland::utils
{
    namespace   
    {
        const inline auto SERVICE = "org.kde.KWin";
        const inline auto SCRIPTING_PATH = "/Scripting";
        const inline auto SCRIPTING_INTERFACE = "org.kde.kwin.Scripting";
        const inline auto SCRIPT_INTERFACE = "org.kde.kwin.Script";
    }

    namespace
    {
        void callScriptMethod(int scriptId, const QString& method)
        {
            auto bus = QDBusConnection::sessionBus();
            QString path = QString("/Scripting/Script%1").arg(scriptId);
            auto msg = QDBusMessage::createMethodCall(SERVICE, path, SCRIPT_INTERFACE, method);
            auto reply = bus.call(msg);
        }
    }

    std::unique_ptr<QTemporaryFile> createScript(const QString &path, const QStringList &args)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return nullptr;
        }

        QString content = QString::fromUtf8(file.readAll());
        for (int i = 0; i < args.size(); ++i)
        {
            content = content.arg(args[i]);
        }

        auto temp = std::make_unique<QTemporaryFile>();
        if (!temp->open())
        {
            return nullptr;
        }
        temp->write(content.toUtf8());
        temp->flush();
        return temp;
    }

    int loadScript(const QString& path, const QString &name)
    {
        QDBusInterface scripting(SERVICE, SCRIPTING_PATH, SCRIPTING_INTERFACE, QDBusConnection::sessionBus());
        scripting.call("unloadScript", name);
        QDBusReply<int> reply = scripting.call("loadScript", path, name);
        return reply.isValid() ? reply.value() : -1;
    }

    void runScript(int scriptId)
    {
        if (scriptId >= 0)
        {
            callScriptMethod(scriptId, "run");
        }
    }

    void stopScript(int scriptId)
    {
        if (scriptId >= 0)
        {
            callScriptMethod(scriptId, "stop");
        }
    }

    void unloadScript(const QString &name)
    {
        QDBusInterface scripting(SERVICE, SCRIPTING_PATH, SCRIPTING_INTERFACE, QDBusConnection::sessionBus());
        scripting.call("unloadScript", name);
    }

    void executeScript(const QString& path, const QString& name, const QStringList &args)
    {
        auto script = createScript(path, args);
        if (!script)
        {
            return;
        }

        int scriptId = loadScript(script->fileName(), name);
        if (scriptId < 0)
        {
            return;
        }

        runScript(scriptId);
        stopScript(scriptId);
        unloadScript(name);
    }
} // sun::monitor::wayland