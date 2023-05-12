<?xml version="1.0" encoding="UTF-8"?>
<!--

  Generate graphviz digraph (see LIMITATIONS below)

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/">
  <xsl:text>
digraph fsm {

    // header
    // rankdir=LR;
    // init [shape = "point", color = "black",style="filled",width=.1,forcelabels=false]; 

    // states</xsl:text>
      <!-- for every condition in the CurrentState switch statement -->
      <xsl:for-each select="
      //block_items[@class='Switch' and ./cond[@class='ID' and @name='CurrentState']]
      /stmt/block_items[@class='Case']
      /expr[@class='ID']
      ">
        <xsl:text>
    "</xsl:text>
        <!-- output name of the condition label -->
        <xsl:value-of select="@name"/><xsl:text>";</xsl:text>
      </xsl:for-each>

    <xsl:text>

    // transitions
</xsl:text>

<!-- locate right hand side value of CurrentState assignment statement inside the InitTemplateFSM() function -->
<!--
    <xsl:text>init -> </xsl:text>
            <xsl:value-of select="
            //ext[@class='FuncDef' and ./decl[@class='Decl' and @name='InitTemplateFSM']]
            //block_items[@class='Assignment' and @op='=' and ./lvalue[@class='ID' and @name='CurrentState']]
            /rvalue/@name"
            />
    <xsl:text>[label = ES_INIT];
</xsl:text>
-->
  <!-- for all = operations to nextState apply templates (BELOW) that are suitable -->
  <xsl:apply-templates select="//*[@op='=' and ./lvalue[@name='nextState'] ]"/>
  <xsl:text>
}</xsl:text>
</xsl:template>

<!--
  Inside top switch statement this template handles assignments to nextState guarded by switch statements 
-->
<xsl:template match="*[@op='=' and ./lvalue[@name='nextState'] and 2=count(ancestor::block_items[@class='Case'])]">
          <xsl:text>    "</xsl:text>
          <!-- top switch statement labels the current state -->
          <xsl:value-of select="
               ancestor::block_items[@class='Case'][2]/expr[@class='ID']/@name
          "/>
          <xsl:text>" -> "</xsl:text>
          <!-- right hand side of assignment supplies the next state -->
          <xsl:value-of select="rvalue/@name"/> 
          <xsl:text>" [label = "</xsl:text>
          <!-- take value of EventType from inner case statement id name  -->
          <xsl:value-of select="@EventLabel"/>
          <xsl:text>" ]; // switch switch
</xsl:text>
  </xsl:template>


<!--
  Inside the top switch statement this template handles assignments to nextState guarded by if statements 
-->
<xsl:template match="*[@op='=' and ./lvalue[@name='nextState'] and 1=count(ancestor::block_items[@class='Case'])]">
          <xsl:text>    "</xsl:text>
          <!-- top level switch statement labels the current state -->
          <xsl:value-of select="
               ancestor::block_items[@class='Case'][1]/expr[@class='ID']/@name
          "/> 
          <xsl:text>" -> "</xsl:text>
          <!-- right hand side of assignment supplies the next state -->
          <xsl:value-of select="rvalue/@name"/> 
          <xsl:text>" [label = "</xsl:text>
          <xsl:value-of select="@EventLabel"/>
      <xsl:text>" ]; // switch if
</xsl:text>
</xsl:template>

</xsl:stylesheet>

<!--
LIMITATIONS

  Code structure:
    * top switch statement on CurrentState 
    * EventType checked using nested switch statements or checked using if statments
    * nextState is assigned inside these nested switch or if statements
    * switch statements can be nested but only one level deep (see EXAMPLE below)
    * if statments can have arbirary nesting
  
  More than two levels of nested switch statements require additional templates 

EXAMPLE

    switch (CurrentState) {
  
    case InitPState: 
        if (ThisEvent.EventType == ES_INIT)
        {
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Hiding: 
        switch (ThisEvent.EventType) { // nested 
            
            case DARK_TO_LIGHT:
                goForward(MOVING_SPEED);
                nextState = Moving;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            default:
                break;
        }
        break;

    case Moving: 
        if (ThisEvent.EventType == LIGHT_TO_DARK) 
        {
            stopMovement();
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        } 
        
        if (ThisEvent.EventType == BUMPER_PRESSED)
        {
           if(ThisEvent.EventParam == 1)
           {
               previousBumpers = 1; 
               backUpRight(TURNING_SPEED);
                ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER,TURN_TIME);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;    
           } 
           // ..
           else if(ThisEvent.EventParam == 8)
           {
                turnRight(TURNING_SPEED);
                ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER,TURN_TIME);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
        }
        break;
        
    default: // all unhandled states fall into here
        break;

    } // end switch on CurrentState
-->