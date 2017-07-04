/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_PICTURE_HPP
#define TGUI_PICTURE_HPP


#include <TGUI/Widgets/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Picture widget
    ///
    /// Signals:
    ///     - DoubleClicked (double left clicked on top of the picture)
    ///     - Inherited signals from ClickableWidget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Picture : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<Picture> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Picture> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Picture();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor to create the picture from a texture
        ///
        /// @param texture  The texture to load the picture from
        /// @param fullyClickable This affects what happens when clicking on a transparent pixel in the image.
        ///                       Is the click caught by the picture, or does the event pass to the widgets behind it?
        ///
        /// @code
        /// Picture picture1("image.png");
        ///
        /// Picture picture2({"image.png", {20, 15, 60, 40}}); // Only load the part of the image from (20,15) to (80,55)
        ///
        /// sf::Texture texture;
        /// texture.loadFromFile("image.png", {20, 15, 60, 40});
        /// Picture picture3(texture);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Picture(const Texture& texture, bool fullyClickable = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new picture widget
        ///
        /// @param texture  The texture to load the picture from
        /// @param fullyClickable This affects what happens when clicking on a transparent pixel in the image.
        ///                       Is the click caught by the picture, or does the event pass to the widgets behind it?
        ///
        /// @return The new picture
        ///
        /// @code
        /// auto picture1 = Picture::create("image.png");
        ///
        /// auto picture2 = Picture::create({"image.png", {20, 15, 60, 40}}); // Load part of the image from (20,15) to (80,55)
        ///
        /// sf::Texture texture;
        /// texture.loadFromFile("image.png", {20, 15, 60, 40});
        /// auto picture3 = Picture::create(texture);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Picture::Ptr create(const Texture& texture = {}, bool fullyClickable = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another picture
        ///
        /// @param picture  The other picture
        ///
        /// @return The new picture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Picture::Ptr copy(Picture::ConstPtr picture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image
        ///
        /// @param texture  The texture to load the picture from
        /// @param fullyClickable This affects what happens when clicking on a transparent pixel in the image.
        ///                       Is the click caught by the picture, or does the event pass to the widgets behind it?
        ///
        /// @code
        /// picture1->setTexture("image.png");
        ///
        /// picture2->setTexture({"image.png", {20, 15, 60, 40}}); // Only load the part of the image from (20,15) to (80,55)
        ///
        /// sf::Texture texture;
        /// texture.loadFromFile("image.png", {20, 15, 60, 40});
        /// picture3->setTexture(texture);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTexture(const Texture& texture, bool fullyClickable = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the filename of the image that was used to load the widget
        ///
        /// @return Filename of loaded image.
        ///         Empty string when no image was loaded yet or when it was loaded directly from an sf::Texture.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::String& getLoadedFilename() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the picture
        ///
        /// @param size  The new size of the picture
        ///
        /// The image will be scaled to fit this size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enables or disable the smooth filter
        ///
        /// When the filter is activated, the texture appears smoother so that pixels are less noticeable.
        /// However if you want the texture to look exactly the same as its source file, you should leave it disabled.
        /// The smooth filter is disabled by default.
        ///
        /// @param smooth True to enable smoothing, false to disable it
        ///
        /// @see isSmooth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSmooth(bool smooth = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Tells whether the smooth filter is enabled or not
        ///
        /// @return True if smoothing is enabled, false if it is disabled
        ///
        /// @see setSmooth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isSmooth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(sf::Vector2f pos) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update(sf::Time elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<Picture>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Sprite  m_sprite;

        // Set to false when clicks on transparent parts of the picture should go to the widgets behind the picture
        bool m_fullyClickable = true;

        // Will be set to true after the first click, but gets reset to false when the second click does not occur soon after
        bool m_possibleDoubleClick = false;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_PICTURE_HPP
