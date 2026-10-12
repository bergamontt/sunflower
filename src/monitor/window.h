#pragma once

#include <QString>

namespace sun::monitor
{
    class WindowImpl
    {
    public:
        [[nodiscard]] virtual QString getName() const = 0;

        virtual void close() const = 0;

        virtual ~WindowImpl() = default;
    };

    class Window
    {
    public:
        explicit Window(std::unique_ptr<WindowImpl> impl) : impl(std::move(impl)) {}

        [[nodiscard]] QString getName() const { return impl->getName(); }

        void close() const { impl->close(); }

        ~Window() = default;

    private:
        std::unique_ptr<WindowImpl> impl;
    };
}