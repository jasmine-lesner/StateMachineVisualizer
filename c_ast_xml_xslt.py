# ( p=`pwd` ; cd "/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/" && /mnt/c/'Program Files'/Microchip/xc32/v4.10/bin/xc32-cpp.exe -I'C:\Program Files/Microchip/xc32/v4.10/pic32mx/include/' -I'C:\Users/chris/OneDrive/Desktop/ECE118/include' -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X' -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/' TemplateFSM.c | egrep -avi '^#|va_list|__attribute__' | perl -pe's{__extension__}{ }g;' > TemplateFSM.cp2 && python3 $p/gpt.py )
# ( p=`pwd` ; cd "/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/" && /mnt/c/'Program Files'/Microchip/xc32/v4.10/bin/xc32-cpp.exe -I'C:\Program Files/Microchip/xc32/v4.10/pic32mx/include/' -I'C:\Users/chris/OneDrive/Desktop/ECE118/include' -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X' -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/' TemplateFSM.c | egrep -avi '^#|va_list|__attribute__' | perl -pe's{__extension__}{ }g;'  > TemplateFSM.cp2 && python3 $p/gpt.py  ) 1>gpt3.xml 2>gtp3.nice 

# import pdb
import re
import sys
from pycparser import c_parser, c_ast, parse_file
from xml.dom import minidom
from lxml import etree as ET
# import xml.etree.ElementTree as ET

def prettify(xml_string):
    reparsed = minidom.parseString(xml_string)
    return reparsed.toprettyxml(indent="  ")

# def compress(text=""):
#     lines = text.split('\n')
#     line_list = []
#     last_line = ""
#     for line in lines:
#         if line != last_line:
#             line_list.append(line)
#         last_line = line
#     result = '\n'.join(line_list)
#     return result

def myshow(node, xnode=ET.Element("root"), buf=sys.stderr, offset=0, attrnames=False, nodenames=False, showcoord=False, _my_node_name=None):
    lead = ' ' * offset
    xnode.set("class", node.__class__.__name__)
    # if nodenames and _my_node_name is not None:
    #     buf.write(lead + node.__class__.__name__ + ' <' + _my_node_name + '>: ')
    # else:
    #     buf.write(lead + node.__class__.__name__ + ': ')

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
        # buf.write(attrstr)

    # if showcoord:
    #     buf.write(' (at %s)' % node.coord)
    # buf.write('\n')

    for (child_name, child) in node.children():
        cxname = re.sub(r'\[.*\]', '', child_name)
        cxnode = ET.SubElement(xnode, cxname)

        myshow(child,
               cxnode,
               buf,
               offset=offset + 2,
               attrnames=attrnames,
               nodenames=nodenames,
               showcoord=showcoord,
               _my_node_name=child_name)

    return xnode

# ast2 = parse_file("TemplateFSM.cp3", use_cpp=False)

ast2 = parse_file("/dev/stdin", use_cpp=False)
xml2 = myshow(ast2, attrnames=True, nodenames=False)

if(len(sys.argv) < 2):
    print(prettify(ET.tostring(xml2, encoding='unicode')))
else:
    result = xml2
    for i in range(1,len(sys.argv)):
        xslt_doc = ET.parse(sys.argv[i])
        transformer = ET.XSLT(xslt_doc)
        result = transformer(result)
        # result = compress(str(transformer(result)))

    print(result)