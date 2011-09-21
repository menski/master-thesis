<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <html><head></head><body>
        <ol Type="I">
          <xsl:apply-templates />
        </ol>
    </body></html>
  </xsl:template>

  <xsl:template match="todo/todo">
    <li style="margin-bottom:3em">
      <xsl:value-of select="title" /> <xsl:apply-templates select="deadline" />
      <ol>
        <xsl:apply-templates select="todo" mode="child"/> 
      </ol>
    </li>
  </xsl:template>

  <xsl:template match="todo/todo" mode="child">
    <li style="margin-bottom:0.5em;padding-top:0.5em">
       <xsl:choose>
        <xsl:when test="@done = 'yes'">
          <span style="color:green">&#9745; </span>
        </xsl:when>
        <xsl:otherwise>
          &#9744;
        </xsl:otherwise>
      </xsl:choose>
      <xsl:value-of select="title" /> <xsl:apply-templates select="deadline" />
      <ol>
        <xsl:apply-templates select="todo" mode="child"/> 
      </ol>
    </li>
  </xsl:template>

  <xsl:template match="deadline">
    (<i><xsl:value-of select="format-number(day,'00')"/>.<xsl:value-of select="format-number(month, '00')"/>.<xsl:value-of select="year"/></i>)
  </xsl:template>

</xsl:stylesheet>
