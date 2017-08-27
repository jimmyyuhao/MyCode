#   Copyright 2012, 2013 David Malcolm <dmalcolm@redhat.com>
#   Copyright 2012, 2013 Red Hat, Inc.
#
#   This is free software: you can redistribute it and/or modify it
#   under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see
#   <http://www.gnu.org/licenses/>.

# Sample python script, to be run by our gcc plugin
# Show the "supergraph": the CFG of all functions, linked by
# interproceduraledges:
import gcc
from gccutils.graph.supergraph import Supergraph
from gccutils import invoke_dot

# We'll implement this as a custom pass, to be called directly before
# 'whole-program'

class ShowSupergraph(gcc.IpaPass):
    def execute(self):
        # (the callgraph should be set up by this point)
        if gcc.is_lto():
            sg = Supergraph(split_phi_nodes=False,
                            add_fake_entry_node=False)
            dot = sg.to_dot('supergraph')
            if 0:
                invoke_dot(dot)

ps = ShowSupergraph(name='show-supergraph')
ps.register_before('whole-program')
