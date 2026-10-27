#pragma once

#include <QString>
#include <QIcon>

namespace sun::monitor
{
    class WindowImpl
    {
    public:
        [[nodiscard]] virtual QString getName() const = 0;

        [[nodiscard]] virtual QIcon getIcon() const = 0;

        virtual void close() const = 0;

        [[nodiscard]] virtual bool operator==(const WindowImpl& other) const = 0;

        virtual ~WindowImpl() = default;
    };

    class Window
    {
    public:
        explicit Window(std::shared_ptr<WindowImpl> impl) : impl(std::move(impl)) {}

        [[nodiscard]] QString getName() const { return impl->getName(); }

        [[nodiscard]] QIcon getIcon() const { return impl->getIcon(); }

        void close() const { impl->close(); }

        bool operator==(const Window& other) const
        {
            if (!impl || !other.impl)
                return !impl && !other.impl;
            return *impl == *other.impl;
        }

        ~Window() = default;

    private:
        std::shared_ptr<WindowImpl> impl;
    };
}