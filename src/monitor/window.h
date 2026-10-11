#pragma once

#include <QString>

namespace sun::monitor
{
    class WindowImpl
    {
    public:
        [[nodiscard]] virtual QString getName() const;

        virtual void minimize() const;

        virtual ~WindowImpl() = 0;
    };

    class Window
    {
    public:
        explicit Window(std::unique_ptr<WindowImpl> impl) : _impl(std::move(impl)) {}

        [[nodiscard]] QString getName() const { return _impl->getName(); }

        void minimize() const { _impl->minimize(); }

        ~Window() = default;

    private:
        std::unique_ptr<WindowImpl> _impl;
    };
}