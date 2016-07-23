/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "camo_instance.hpp"

namespace camo
{
    instance::~instance()
    {
        
    }
    
    void instance::load_patch(const std::string &name, const std::string &path)
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
        }
        m_patch = xpd::instance::load(name, path);
        if(static_cast<bool>(m_patch))
        {
            m_playhead_tie = xpd::tie(std::to_string(m_patch.unique_id()) + "-playhead");
        }
        else
        {
            send(xpd::console::post(xpd::console::error, std::string("instance can't find the patch : ") + name));
        }
    }
    
    
    void instance::close_patch()
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
            m_playhead_tie = xpd::tie();
        }
    }
    
    void instance::add_listener(listener& l)
    {
        m_listeners.insert(&l);
    }
    
    void instance::remove_listener(listener& l)
    {
        m_listeners.erase(&l);
    }
}

