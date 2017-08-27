.. Copyright 2011 David Malcolm <dmalcolm@redhat.com>
   Copyright 2011 Red Hat, Inc.

   This is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.

Working with functions and control flow graphs
==============================================

Many of the plugin events are called for each function within the source code
being compiled.  Each time, the plugin passes a :py:class:`gcc.Function`
instance as a parameter to your callback, so that you can work on it.

You can get at the control flow graph of a :py:class:`gcc.Function` via its
``cfg`` attribute.  This is an instance of :py:class:`gcc.Cfg`.

.. py:class:: gcc.Function

   Wrapper around one of GCC's ``struct function *``

   .. py:attribute:: cfg

      An instance of :py:class:`gcc.Cfg` for this function (or None during early
      passes)

   .. py:attribute:: decl

      The declaration of this function, as a :py:class:`gcc.FunctionDecl`

   .. py:attribute:: local_decls

      List of :py:class:`gcc.VarDecl` for the function's local variables.  It
      does not contain arguments; for those see the `arguments` property of
      the function's `decl`.

      Note that for locals with initializers, `initial` only seems to get set
      on those `local_decls` that are static variables.  For other locals, it
      appears that you have to go into the gimple representation to locate
      assignments.

   .. py:attribute:: start

      The :py:class:`gcc.Location` of the beginning of the function

   .. py:attribute:: end

      The :py:class:`gcc.Location` of the end of the function

   .. py:attribute:: funcdef_no

      Integer: a sequence number for profiling, debugging, etc.

.. py:class:: gcc.Cfg

  A ``gcc.Cfg`` is a wrapper around GCC's `struct control_flow_graph`.

  .. py:attribute:: basic_blocks

     List of :py:class:`gcc.BasicBlock`, giving all of the basic blocks within
     this CFG

  .. py:attribute:: entry

     Instance of :py:class:`gcc.BasicBlock`: the entrypoint for this CFG

  .. py:attribute:: exit

     Instance of :py:class:`gcc.BasicBlock`: the final one within this CFG

  .. py:method:: get_block_for_label(labeldecl)

     Given a :py:class:`gcc.LabelDecl`, get the corresponding
     :py:class:`gcc.BasicBlock`

  You can use ``gccutils.cfg_to_dot`` to render a gcc.Cfg as a graphviz
  diagram.  It will render the diagram, showing each basic block, with
  source code on the left-hand side, interleaved with the "gimple"
  representation on the right-hand side.  Each block is labelled with its
  index, and edges are labelled with appropriate flags.

  For example, given this sample C code:

    .. literalinclude:: ../test.c
      :lines: 33-48
      :language: c

  then the following Python code::

    dot = gccutils.cfg_to_dot(fun.cfg)
    gccutils.invoke_dot(dot)

  will render a CFG bitmap like this:

    .. figure:: sample-gimple-cfg.png
      :scale: 50 %
      :alt: image of a control flow graph

.. py:class:: gcc.BasicBlock

  A ``gcc.BasicBlock`` is a wrapper around GCC's `basic_block` type.

  .. py:attribute:: index

     The index of the block (an int), as seen in the cfg_to_dot rendering.

  .. py:attribute:: preds

     The list of predecessor :py:class:`gcc.Edge` instances leading into this
     block

  .. py:attribute:: succs

     The list of successor :py:class:`gcc.Edge` instances leading out of this
     block

  .. py:attribute:: phi_nodes

     The list of :py:class:`gcc.GimplePhi` phoney functions at the top of this
     block, if appropriate for this pass, or None

  .. py:attribute:: gimple

     The list of :py:class:`gcc.Gimple` instructions, if appropriate for this
     pass, or None

  .. py:attribute:: rtl

     The list of :py:class:`gcc.Rtl` expressions, if appropriate for this
     pass, or None


.. py:class:: gcc.Edge

  A wrapper around GCC's `edge` type.

  .. py:attribute:: src

     The source :py:class:`gcc.BasicBlock` of this edge

  .. py:attribute:: dest

     The destination :py:class:`gcc.BasicBlock` of this edge

  .. py:attribute:: true_value

     Boolean: `True` if this edge is taken when a :py:class:`gcc.GimpleCond`
     conditional is true, `False` otherwise

  .. py:attribute:: false_value

     Boolean: `True` if this edge is taken when a :py:class:`gcc.GimpleCond`
     conditional is false, `False` otherwise

  .. py:attribute:: complex

     Boolean: `True` if this edge is "special" e.g. due to
     exception-handling, or some other kind of "strange" control flow transfer,
     `False` otherwise

  .. various other EDGE_ booleans, though it's not clear that they should be
     documented
