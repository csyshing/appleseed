
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "messagecontext.h"

// appleseed.renderer headers.
#include "renderer/modeling/entity/entity.h"

using namespace std;

namespace renderer
{

//
// MessageContext class implementation.
//

struct MessageContext::Impl
{
    string m_message;
};

MessageContext::MessageContext()
  : impl(0)
{
}

MessageContext::MessageContext(const char* message)
  : impl(0)
{
    set_message(message);
}

MessageContext::~MessageContext()
{
    delete impl;
}

bool MessageContext::empty() const
{
    return impl == 0 || impl->m_message.empty();
}

const char* MessageContext::get() const
{
    return impl ? impl->m_message.c_str() : "";
}

void MessageContext::set_message(const char* message)
{
    if (impl == 0)
        impl = new Impl();

    impl->m_message = message;
}


//
// EntityDefMessageContext class implementation.
//

EntityDefMessageContext::EntityDefMessageContext(
    const char*     entity_type,
    const Entity*   entity)
{
    set_message("while defining " + string(entity_type) + " \"" + entity->get_path() + "\"");
}

}   // namespace renderer
