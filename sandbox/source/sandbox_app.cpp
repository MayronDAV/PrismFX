#include "PrismFX/prismfx.h"
#include "PrismFX/core/entry_point.h"


class Sandbox : public PFX::Application
{
    public:
        Sandbox() = default;
        ~Sandbox() = default;
};


PFX::Application* PFX::CreateApplication()
{
    return new Sandbox();
}