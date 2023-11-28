#pragma once
#include "main.h"

// this is a base class for all commands used in my project, particularly GUI part; it's intended to be inherited from by classes representing commands, which will allow for easy undo/redo implementation once command queue is stored inside CommandManager
class Command
{
public:
    enum class State
    {
        UNDONE,
        DONE,
        REDONE
    };
protected:
    State state;
public:
    virtual ~Command() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
    virtual bool redo() = 0;
    virtual wxString getDescription() = 0;
    virtual wxString getShortDescription() = 0;
    virtual bool isUndoable() = 0;
    virtual bool isRedoable() = 0;
    virtual bool isRepeatable() = 0;
    virtual State getState() = 0;

    RTTR_REGISTRATION_FRIEND
};

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Command>("Command")
        .method("execute", &Command::execute)
        .method("undo", &Command::undo)
        .method("redo", &Command::redo)
        .method("getDescription", &Command::getDescription)
        .method("getShortDescription", &Command::getShortDescription)
        .method("isUndoable", &Command::isUndoable)
        .method("isRedoable", &Command::isRedoable)
        .method("isRepeatable", &Command::isRepeatable)
        .method("getState", &Command::getState)
        .enumeration<Command::State>("State")
            (
                value("UNDONE", Command::State::UNDONE),
                value("DONE", Command::State::DONE),
                value("REDONE", Command::State::REDONE)
            );
    registerExtra<Command>();
}
