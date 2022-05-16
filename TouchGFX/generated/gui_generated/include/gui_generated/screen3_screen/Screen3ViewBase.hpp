/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN3VIEWBASE_HPP
#define SCREEN3VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class Screen3ViewBase : public touchgfx::View<Screen3Presenter>
{
public:
    Screen3ViewBase();
    virtual ~Screen3ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void sendHello()
    {
        // Override and implement this function in Screen3
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Image image1;
    touchgfx::ButtonWithLabel buttonWithLabel1;
    touchgfx::TextAreaWithOneWildcard textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::ButtonWithLabel sendHelloBtn;
    touchgfx::Box boxDoors;
    touchgfx::TextArea textArea3;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA2_SIZE = 100;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen3ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN3VIEWBASE_HPP
