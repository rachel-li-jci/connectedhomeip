/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#pragma once

#include <lib/mdns/minimal/core/Constants.h>
#include <lib/mdns/minimal/core/QName.h>

namespace mdns {
namespace Minimal {

/// Filter used to determine what kind of a reply is acceptable
/// or not
class ReplyFilter
{
public:
    virtual ~ReplyFilter() {}

    /// Returns true if specified answer should be sent back as a reply
    virtual bool Accept(QType qType, QClass qClass, FullQName qname) = 0;
};

} // namespace Minimal
} // namespace mdns
