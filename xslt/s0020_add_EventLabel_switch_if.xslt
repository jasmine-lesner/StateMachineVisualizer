<?xml version="1.0" encoding="UTF-8"?>
<!--

  Handle assignments to nextState guarded by if statements 

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes" />
  <xsl:strip-space elements="*" />

  <xsl:template
    match="
    *[
      @op='=' 
      and ./lvalue[@name='nextState'] 
      and 1=count(ancestor::block_items[@class='Case'])
    ]
  ">

    <xsl:variable name="EventType">
      <!-- locate first (any) enclosing context 
      (still inside a switch statement case block) 
      that tests EventType (such as some if statement) -->
      <xsl:for-each
        select="
                ancestor::*[
                  ancestor::block_items[@class='Case']
                  and .//*[@op='==' and .//field[@name='EventType']]
                ][1]
      ">
        <!-- inside the first enclosing context that tests EventType take the value it is tested
        against -->
        <xsl:value-of
          select="
                .//*[@op='==' and .//field[@name='EventType']]
                /right/@name
        " />
      </xsl:for-each>
    </xsl:variable>

    <xsl:variable name="EventParam">
      <!-- locate first (any) enclosing context 
      (still inside a switch statement case block) 
      that tests EventParam (such as some if statement) -->
      <xsl:for-each
        select="
                ancestor::*[
                  ancestor::block_items[@class='Case']
                  and .//*[@op='==' and .//field[@name='EventParam']]
                ][1]
      ">
        <!-- inside the enclosing context that tests EventParam take the name of what it is tested
        against -->
        <xsl:value-of
          select="
                .//*[@op='==' and .//field[@name='EventParam']]
                /right/@name
        " />
        <!-- since the thing EventParam is tested against may be a constant such as 
        <right class="Constant" type="int" value="0"/> 
        and constants have no name attribute also try to take the value of the thing
        -->
        <xsl:value-of
          select="
                .//*[@op='==' and .//field[@name='EventParam']]
                /right/@value
        " />
      </xsl:for-each>
    </xsl:variable>

    <xsl:variable name="EventLabel">
      <xsl:choose>
        <xsl:when test=" normalize-space($EventParam)='' ">
          <xsl:copy-of select="normalize-space($EventType)" />
        </xsl:when>
        <xsl:otherwise>
          <xsl:copy-of select="normalize-space($EventType)" />
          <xsl:text>(</xsl:text>
          <xsl:copy-of select="normalize-space($EventParam)" />
          <xsl:text>)</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:copy>
      <xsl:choose>
        <xsl:when test=" normalize-space($EventType)='' ">
          <!-- if EventType not identified do not add EventLabel attribute -->
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="EventLabel">
            <xsl:copy-of select="$EventLabel" />
          </xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates select="@*|node()" />
    </xsl:copy>

  </xsl:template>

  <!-- identity transform - copy all input nodes to output -->
  <xsl:template match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()" />
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>