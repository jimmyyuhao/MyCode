#   Copyright 2011 David Malcolm <dmalcolm@redhat.com>
#   Copyright 2011 Red Hat, Inc.
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

# Verify examining details of functions

import gcc
from gccutils import pprint

def on_pass_execution(p, fn):
    if p.name in '*warn_function_return':
        assert isinstance(fn, gcc.Function)
        print('fn: %r' % fn)

        assert isinstance(fn.decl, gcc.FunctionDecl)
        print('fn.decl.name: %r' % fn.decl.name)

        if fn.cfg: # None for some early passes
            print('CFG:')
            for bb in fn.cfg.basic_blocks:
                print('  BLOCK %i' % bb.index)
                if bb.gimple:
                    for i,stmt in enumerate(bb.gimple):
                        print('  gimple[%i]:' % i)
                        print('    str(stmt): %r' % str(stmt))
                        print('    repr(stmt): %r' % repr(stmt))
                        if isinstance(stmt, gcc.GimpleCond):
                            print('    stmt.lhs: %r' % stmt.lhs)
                            print('    stmt.exprcode: %r' % stmt.exprcode)
                            print('    stmt.rhs: %r' % stmt.rhs)
                            print('    stmt.true_label: %r' % stmt.true_label)
                            print('    stmt.false_label: %r' % stmt.false_label)

gcc.register_callback(gcc.PLUGIN_PASS_EXECUTION,
                      on_pass_execution)
