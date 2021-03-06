// libTorrent - BitTorrent library
// Copyright (C) 2005-2007, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#include "config.h"

#include "chunk_utils.h"
#include "download.h"
#include "exceptions.h"

#include "download/download_wrapper.h"

#include "data/chunk.h"
#include "data/chunk_list.h"

namespace torrent {

std::vector<vm_mapping>
chunk_list_mapping(Download* download) {
  ChunkList* chunk_list = download->ptr()->main()->chunk_list();

  std::vector<vm_mapping> mappings;

  for (ChunkList::const_iterator itr = chunk_list->begin(), last = chunk_list->end(); itr != last; itr++) {
    if (!itr->is_valid())
      continue;

    for (Chunk::const_iterator itr2 = itr->chunk()->begin(), last2 = itr->chunk()->end(); itr2 != last2; itr2++) {
      if (itr2->mapped() != ChunkPart::MAPPED_MMAP)
        continue;

      vm_mapping val = { itr2->chunk().ptr(), itr2->chunk().size_aligned() };
      mappings.push_back(val);
    }
  }

  return mappings;
}

}
