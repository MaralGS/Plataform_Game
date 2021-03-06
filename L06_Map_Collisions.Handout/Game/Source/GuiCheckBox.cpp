#include "GuiCheckBox.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        // L14: TODO 3: Update the state of the GUiButton according to the mouse position
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiCheckBox::Draw(Render* render)
{
    // Draw the right button depending on state
    if (!debugDraw)
    {
        switch (state)
        {
        case GuiControlState::DISABLED:
        {
            if (checked) render->DrawRectangle(bounds, 100, 0, 100, 100);
            else render->DrawRectangle(bounds, 0, 0, 0, 100);
        } break;
        case GuiControlState::NORMAL:
        {
            if (checked) render->DrawRectangle(bounds, 0, 0, 0, 125);
            else render->DrawRectangle(bounds, 255, 255, 255, 100 );
        } break;
        case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 255, 50 );
            break;
        case GuiControlState::PRESSED: render->DrawRectangle(bounds, 255, 255, 255, 150 );
            break;
        case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
            break;
        default:
            break;
        }
    }

    else
    {
        switch (state)
        {
        case GuiControlState::DISABLED:
        {
            if (checked) render->DrawRectangle(bounds, 100, 0, 100, 255 );
            else render->DrawRectangle(bounds, 0, 0, 0, 255);
        } break;
        case GuiControlState::NORMAL:
        {
            if (checked) render->DrawRectangle(bounds, 255, 255, 255, 255);
            else render->DrawRectangle(bounds, 0, 255, 0, 255);
        } break;
        case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 0, 255);
            break;
        case GuiControlState::PRESSED: render->DrawRectangle(bounds, 0, 0, 255, 255);
            break;
        case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
            break;
        default:
            break;
        }
    }

    return false;
}
