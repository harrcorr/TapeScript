<h1>TapeScript</h1>
<p>
TapeScript is a interpreted programming language/very rough cpu emulator I built for fun <br/>
Feel free to make a PR if you wanna upgrade it
</p>


</p>
<h2> Features of TapeScript</h2>
 <li/> Basic ADD/SUB arithmetic operations</br>
 <li/> A Ranging in size Tape/memory</br>
 <li/> Adjustable clock speed</br>
 <li/> Fully visible stack and registers </br>
 <li/> Support for conditional branching </br>

<br/>
<h2> Datatypes </h2>
<table>
<thead>
<tr>
<th>Name</th>
<th>Internal c++ Datatype</th>
<th>How to specify</th>
</tr>
</thead>
<thead>
<tr>
<th>INT</th>
<th>int</th>
<th>How to specify</th>
</tr>
</thead>
<thead>
<tr>
<th>REGISTER</th>
<th>std::string</th>
<th>"(register name)"</th>
</tr>
</thead>
<thead>
<tr>
<th>STRING</th>
<th>std::string</th>
<th>no explicit specification required</th>
</tr>
</thead>
<th>MEM</th>
<th>int</th>
<th>use 0x prefix on whatever number</th>
</tr>
</thead>
<th>OTHER</th>
<th>std::string/int</th>
<th>no explicit declaration required</th>
</tr>
</thead>
</table>

<h2> Instruction Set </h2>

<table>
<thead>
<tr>
<th>Instruction</th>
<th>Args</th>
<th>Usage</th>
</tr>
</thead>
<thead>
<tr>
<th>LOADA</th>
<th>INT/STRING</th>
<th>Load an integer into the A register either directly or from another register</th>
</tr>
</thead>

<tr>
<th>LOADB</th>
<th>INT/STRING</th>
<th>Load an integer into the B register either directly or from another register </th>
</tr>
</thead>
<thead>
<tr>
<th>LOADC</th>
<th>INT/STRING</th>
<th>Load an integer into the C register either directly or from another register</th>
</tr>
</thead>
<thead>
<tr>
<th>PRINT</th>
<th>REGISTER/MEM/OTHER</th>
<th>Print data either from a register a memory address or directly print whatever is specified in the file</th>
</tr>
</thead>
<thead>
<th>STORE</th>
<th>REGISTER</th>
<th>Store data from at the current StackPointer location</th>
</tr>
</thead>
<thead>
<th>SHIFTLEFT</th>
<th>N/A</th>
<th>Shift the StackPointer left (-1)</th>
</tr>
</thead>
<thead>
<th>SHIFTRIGHT</th>
<th>N/A</th>
<th>Shift the StackPointer right (+1)</th>
</tr>
</thead>

<th>SET</th>
<th>REGISTER , REGISTER</th>
<th>Set data from any register to any other register</th>
</tr>
</thead>
<thead>
<th>ADD</th>
<th>REGISTER , REGISTER</th>
<th>Compute add operation of the data in the two specified registers and store in the "MathOp" register</th>
</tr>
</thead>
<thead>
<th>SUB</th>
<th>REGISTER , REGISTER</th>
<th>Compute subtract operation of the data in the two specified registers and store in the "MathOp" register</th>
</tr>
</thead>
<thead>
<th>JMP</th>
<th>LABEL</th>
<th>This will change the "InstructionPointer" register to the location of the specified label</th>
</tr>
</thead>
<thead>
<th>IF</th>
<th>REGISTER , REGISTER , (any instruction)</th>
<th>if the data in two specified registers is equal execute anything placed after the second register</th>
</tr>
</thead>

</table>

<h1>Q/A</h1>
<p>
<b>Does it do much?</br></b>
No.
<br/>
<b>Is it useful?</br></b>
No.
<br/>
<b>Does it work?</br></b>
Mhmm kinda...
<br/>
<b>Why does a programming language have registers?</b>
<br/>
To be honest i have no idea
<br/>
<b>Ive now seen how amazing this code is how do i use it?</b><br/>
Simply clone the directory and run make i have only used standard g++ libs
and one linux lib
if you dont have the linux lib take it out and replace
<code>main.cpp:103 system("clear")</code> and <code> main.cpp:97 sleep(clockSpeed)</code> with your operating systems equivalent
</br>
