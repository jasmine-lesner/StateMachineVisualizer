import io
import re
import sys
from subprocess import check_output # what is this?
from pycparser import c_parser, c_ast, parse_file, CParser
from lxml import etree as ET
from xml.dom import minidom

def prettify(xml_string):
    reparsed = minidom.parseString(xml_string)
    return reparsed.toprettyxml(indent="  ")

# based on show() from /home/jml/smv/lib/python3.10/site-packages/pycparser/c_ast.py
def myshow(node, xnode=ET.Element("ast",attrib=None, nsmap=None), buf=sys.stderr, offset=0, attrnames=False, nodenames=False, showcoord=False, _my_node_name=None):
    lead = ' ' * offset
    xnode.set("class", node.__class__.__name__)
    # if nodenames and _my_node_name is not None:
    #     buf.write(lead + node.__class__.__name__ + ' <' + _my_node_name + '>: ')
    # else:
    #     buf.write(lead + node.__class__.__name__ + ': ')
    nodeid=('%s' % node.coord)
    lineandoffset=re.sub(r'^.*?:', '', nodeid)
    line=re.sub(r':.*?$', '', lineandoffset)
    xnode.set("line", line)

    if node.attr_names:
        if attrnames:
            nvlist = [(n, getattr(node, n)) for n in node.attr_names]
            attrstr = ', '.join('%s=%s' % nv for nv in nvlist)
            for nv in nvlist:
                # pdb.set_trace()
                if(nv[1] == None):
                    xnode.set(nv[0], "")
                else:
                    xnode.set(nv[0], str(nv[1]))
        else:
            vlist = [getattr(node, n) for n in node.attr_names]
            attrstr = ', '.join('%s' % v for v in vlist)

    for (child_name, child) in node.children():
        cxname = re.sub(r'\[.*\]', '', child_name)
        cxnode = ET.SubElement(xnode, cxname,attrib=None, nsmap=None)

        myshow(child,
               cxnode,
               buf,
               offset=offset + 2,
               attrnames=attrnames,
               nodenames=nodenames,
               showcoord=showcoord,
               _my_node_name=child_name)

    return xnode

stdin = open("/dev/stdin", "r").read()

# define container for code lines and abstract syntax tree
rootnode=ET.Element("root",attrib=None, nsmap=None)
codenode=ET.Element("code",attrib=None, nsmap=None)
astnode=ET.Element("ast",attrib=None, nsmap=None) 

# attach code lines
n = 1
for line in stdin.splitlines():
    ET.SubElement(codenode, "line",attrib=None, nsmap=None).text = line
    codenode[-1].set("n", str(n))
    n += 1
rootnode.append(codenode)

# attach abstract syntax tree
parser = CParser()
ast2 = parser.parse(stdin, "stdin")
astnode = myshow(ast2, attrnames=True, nodenames=False)
rootnode.append(astnode)

# output the result
print(prettify(ET.tostring(rootnode)))
