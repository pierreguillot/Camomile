/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */
#pragma once

#include "PdPatch.hpp"

namespace pd
{
    class Graph;
    class Label;
    
    // ==================================================================================== //
    //                                      OBJECT                                          //
    // ==================================================================================== //
    
    //! @brief The Pure Data Object.
    //! @details The Instance is a wrapper for the Pure Data's native comment.
    //! With the default constructor, theObjectGui won't be initialized. A valid
    //! Object should be created via a Patch. The Gui should be used as tempory object,
    //! because it locks the Patch.
    class Object
    {
    public:
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! another class.
        Object() noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Object(Object const& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Object& operator=(Object const& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Object() noexcept;
        
        //! @brief The text of the Object.
        std::string getText() const;
        
        //! @brief The name of the Object.
        std::string getName() const;
        
        //! @brief The bounds of the Object.
        virtual std::array<int, 4> getBounds() const noexcept;
        
    protected:
        
        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! Patch to retrieve an Object.
        Object(void* ptr, Patch const& patch) noexcept;
        
        void*   m_ptr;
        Patch   m_patch;
        friend class Patch;
    };
    
    // ==================================================================================== //
    //                                          GUI                                         //
    // ==================================================================================== //
    
    //! @brief The Pure Data GUI.
    //! @details The Instance is a wrapper for the Pure Data's native GUI.
    //! With the default constructor, the Gui won't be initialized. A valid
    //! Gui should be created via a Patch. The Gui should be used as tempory object,
    //! because it locks the Patch.
    class Gui : public Object
    {
    public:
        
        enum class Type : size_t
        {
            Undefined        = 0,
            HorizontalSlider = 1,
            VerticalSlider   = 2,
            Toggle           = 3,
            Number           = 4,
            HorizontalRadio  = 5,
            VerticalRadio    = 6,
            Bang             = 7,
            Panel            = 8,
            VuMeter          = 9,
            Comment          = 10,
            AtomNumber       = 11,
            AtomSymbol       = 12,
            Array            = 13
        };
        
        //! @brief The constructor for an empty Object.
        //! @details Creates an Object that can be used as an empty reference inside
        //! another class.
        Gui() noexcept;
        
        //! @brief The copy constructor.
        //! @details Creates a copy of an Object and increments his counter.
        Gui(Gui const& other) noexcept;
        
        //! @brief The copy operator.
        //! @details Copies the Object and increments his counter.
        Gui& operator=(Gui const& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Object will be destroyed if no other copy exists.
        virtual ~Gui() noexcept;
        
        //! @brief The class name of the Object.
        Type getType() const noexcept;
        
        //! @brief If the GUI is an IEM's GUI.
        bool isIEM() const noexcept;
        
        //! @brief If the GUI is an Atom GUI (AtomNumber or AtomSymbol).
        bool isAtom() const noexcept;
        
        int getFontSize() const noexcept;
        
        float getMinimum() const noexcept;
        
        float getMaximum() const noexcept;
        
        float getValue() const noexcept;
        
        void setValue(float value) noexcept;
        
        size_t getNumberOfSteps() const noexcept;
        
        unsigned int getBackgroundColor() const noexcept;
        
        unsigned int getForegroundColor() const noexcept;
        
        std::string getSymbol() const noexcept;
        
        void setSymbol(std::string const& value) noexcept;
        
        std::array<int, 4> getBounds() const noexcept override;
        
        bool jumpOnClick() const noexcept;
        
        bool isLogScale() const noexcept;
        
        Graph getGraph() const noexcept;
        
        Label getLabel() const noexcept;
    private:

        //! @brief The constructor for a new Object.
        //! @details Creates a new valid Object. You should never have to use it. Use the
        //! Patch to retrieve an Object.
        Gui(void* ptr, Patch const& patch) noexcept;
        
        Type        m_type;
        friend class Patch;
    };
    
    // ==================================================================================== //
    //                                      LABEL                                           //
    // ==================================================================================== //
    
    class Label
    {
    public:
        Label() noexcept;
        Label(Label const& other) noexcept;
        Label(std::string const& text, unsigned int color, int x, int y) noexcept;
        
        std::string getText() const noexcept { return m_text; }
        unsigned int getColor() const noexcept { return m_color; }
        std::array<int, 2> getPosition() const noexcept { return m_position; }
    private:
        Label(Gui const& gui) noexcept;
        std::string const        m_text;
        unsigned int const       m_color;
        std::array<int, 2> const m_position;
        friend class Gui;
    };
    
    // ==================================================================================== //
    //                                      GRAPH                                           //
    // ==================================================================================== //
    
    class Graph
    {
    public:
        Graph() noexcept;
        Graph(Instance& instance, std::string const& name) noexcept;
        Graph(Graph const& other) noexcept;
        
        std::string getName() const noexcept;
        bool isDrawingPoints() const noexcept;
        bool isDrawingCurve() const noexcept;
        bool isGOP() const noexcept;
        
        void read(std::vector<float>& output) const;
        void write(std::vector<float> const& input);
        void writeSample(const size_t pos, float const input);
    private:
        
        Graph(void* ptr, Instance& instance) noexcept;
        
        Instance*   m_instance;
        std::string m_name;
        size_t      m_drawing_mode;
        bool        m_is_gop;
        friend class Gui;
    };
}

