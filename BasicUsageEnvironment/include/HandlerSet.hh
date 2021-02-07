// Copyright (c) 1996-2012 Live Networks, Inc.  All rights reserved.
// Basic Usage Environment: for a simple, non-scripted, console application
// C++ header

#ifndef _HANDLER_SET_HH
#define _HANDLER_SET_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

////////// HandlerSet (etc.) definition //////////

class HandlerDescriptor
{
    HandlerDescriptor(HandlerDescriptor *nextHandler);
    virtual ~HandlerDescriptor();

public:
    int socketNum;
    int conditionSet;
    TaskScheduler::BackgroundHandlerProc *handlerProc;
    void *clientData;

private:
    // Descriptors are linked together in a doubly-linked list:
    friend class HandlerSet;
    friend class HandlerIterator;
    HandlerDescriptor *fNextHandler;
    HandlerDescriptor *fPrevHandler;
};

class HandlerSet
{
public:
    HandlerSet();
    virtual ~HandlerSet();

    void assignHandler(int socketNum, int conditionSet, TaskScheduler::BackgroundHandlerProc *handlerProc, void *clientData);
    void clearHandler(int socketNum);
    void moveHandler(int oldSocketNum, int newSocketNum);

private:
    HandlerDescriptor *lookupHandler(int socketNum);

private:
    friend class HandlerIterator;
    HandlerDescriptor fHandlers;
};

class HandlerIterator
{
public:
    HandlerIterator(HandlerSet &handlerSet);
    virtual ~HandlerIterator();

    HandlerDescriptor *next(); // returns NULL if none
    void reset();

private:
    HandlerSet &fOurSet;
    HandlerDescriptor *fNextPtr;
};

#endif
