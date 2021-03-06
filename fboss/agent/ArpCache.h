/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include "fboss/agent/SwSwitch.h"
#include "fboss/agent/NeighborCache.h"
#include "fboss/agent/types.h"
#include "fboss/agent/state/PortDescriptor.h"

#include <folly/MacAddress.h>
#include <folly/IPAddressV4.h>
#include <list>
#include <string>

namespace facebook { namespace fboss {

enum ArpOpCode : uint16_t;

class ArpCache : public NeighborCache<ArpTable> {
 public:
  ArpCache(SwSwitch* sw, const SwitchState* state,
           VlanID vlanID, std::string vlanName, InterfaceID intfID);

  void sentArpRequest(folly::IPAddressV4 ip);
  void receivedArpMine(folly::IPAddressV4 ip,
                       folly::MacAddress mac,
                       PortDescriptor port,
                       ArpOpCode op);
  void receivedArpNotMine(folly::IPAddressV4 ip,
                          folly::MacAddress mac,
                          PortDescriptor port,
                          ArpOpCode op);

  void probeFor(folly::IPAddressV4 ip) const override;

  std::list<ArpEntryThrift> getArpCacheData();

};

}} // facebook::fboss
