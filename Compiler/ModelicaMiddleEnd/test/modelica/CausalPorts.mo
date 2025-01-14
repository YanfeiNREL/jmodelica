/*
	Copyright (C) 2019 Modelon AB

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

within ;
package CausalPorts

model Flow1
    connector C
        Real a;
        flow Real b;
    end C;
    
    C c;
equation
    c.a = 1;
annotation(__JModelica(UnitTesting(tests={
    TransformCanonicalTestCase(
        description="No zero equation for top level flow connector variables when using causal_ports",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Flow1
 potential Real c.a;
 flow Real c.b;
equation
 c.a = 1;
end CausalPorts.Flow1;
")})));
end Flow1;


model Flow2
    connector C
        Real a;
        flow Real b;
    end C;
    
    model A
        C c;
    end A;
    
    C c;
    A a1, a2;
equation
    c.a = 1;
    a2.c.a = 2;
    connect(a1.c, c);
annotation(__JModelica(UnitTesting(tests={
    TransformCanonicalTestCase(
        description="causal_ports only affect top level connectors",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Flow2
 potential Real c.a;
 flow Real c.b;
 Real a1.c.a;
 Real a1.c.b;
 Real a2.c.a;
 Real a2.c.b;
equation
 c.a = 1;
 a2.c.a = 2;
 a1.c.a = c.a;
 a1.c.b - c.b = 0.0;
 a2.c.b = 0.0;
end CausalPorts.Flow2;
")})));
end Flow2;


model Stream1
    connector C
        Real p;
        flow Real f;
        stream Real s;
    end C;
    C c;
equation
    c.p = time;
    c.s = inStream(c.s);
annotation(__JModelica(UnitTesting(tests={
    FlatteningTestCase(
        description="Top level stream connector variables get an inStream variable when using causal_ports",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream1
 potential Real c.p;
 flow Real c.f;
 stream Real c.s annotation(__Modelon(internal(instream = \"c.s__instream_\")));
 inStream Real c.s__instream_;
equation
 c.p = time;
 c.s = inStream(c.s);
end CausalPorts.Stream1;
"), TransformCanonicalTestCase(
        description="Top level stream connector variables get an inStream variable when using causal_ports",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream1
 potential Real c.p;
 flow Real c.f;
 stream Real c.s annotation(__Modelon(internal(instream = \"c.s__instream_\")));
 inStream Real c.s__instream_;
equation
 c.p = time;
 c.s = c.s__instream_;
end CausalPorts.Stream1;
"), FClassMethodTestCase(
        description="inStream variable is treated as input",
        causal_ports=true,
        eliminate_alias_variables=false,
        eliminate_linear_equations=false,
        variability_propagation=false,
        methodName="printDAEInitBLT",
        methodResult="
--- Solved equation ---
c.p := time

--- Solved equation ---
c.s := c.s__instream_
-------------------------------
")})));
end Stream1;


model Stream2
    connector C
        Real p;
        flow Real f;
        stream Real s;
    end C;
    
    model A
        C c;
    end A;
    
    C c;
    A a1, a2;
equation
    c.p = time;
    c.s = inStream(c.s);
    connect(a1.c, c);
    a2.c.p = 2 * time;
    a2.c.s = inStream(a2.c.s);
annotation(__JModelica(UnitTesting(tests={
    TransformCanonicalTestCase(
        description="causal_ports only affect top level connectors",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream2
 potential Real c.p;
 flow Real c.f;
 stream Real c.s annotation(__Modelon(internal(instream = \"c.s__instream_\")));
 inStream Real c.s__instream_;
 Real a1.c.p;
 Real a1.c.f;
 Real a1.c.s;
 Real a2.c.p;
 Real a2.c.f;
 Real a2.c.s;
equation
 c.p = time;
 c.s = c.s__instream_;
 a2.c.p = 2 * c.p;
 a2.c.s = a2.c.s;
 a1.c.f - c.f = 0.0;
 a1.c.p = c.p;
 c.s = a1.c.s;
 a2.c.f = 0.0;
end CausalPorts.Stream2;
")})));
end Stream2;


model Stream3
    connector C
        Real p;
        flow Real f;
        stream Real[0] s1;
        stream Real[2] s2;
    end C;
    C c;
equation
    c.p = time;
    c.s1 = inStream(c.s1);
    c.s2 = inStream(c.s2);
annotation(__JModelica(UnitTesting(tests={
    FlatteningTestCase(
        description="Stream arrays create the same number of inStream variables",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream3
 potential Real c.p;
 flow Real c.f;
 stream Real c.s1[0] annotation(__Modelon(internal(instream = \"c.s1__instream_\")));
 inStream Real c.s1__instream_[0];
 stream Real c.s2[2] annotation(__Modelon(internal(instream = \"c.s2__instream_\")));
 inStream Real c.s2__instream_[2];
equation
 c.p = time;
 c.s1[1:0] = inStream(c.s1[1:0]);
 c.s2[1:2] = inStream(c.s2[1:2]);
end CausalPorts.Stream3;
"), TransformCanonicalTestCase(
        description="Stream arrays create the same number of inStream variables",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream3
 potential Real c.p;
 flow Real c.f;
 stream Real c.s2[1] annotation(__Modelon(internal(instream = \"c.s2__instream_\")));
 stream Real c.s2[2] annotation(__Modelon(internal(instream = \"c.s2__instream_\")));
 inStream Real c.s2__instream_[1];
 inStream Real c.s2__instream_[2];
equation
 c.p = time;
 c.s2[1] = c.s2__instream_[1];
 c.s2[2] = c.s2__instream_[2];
end CausalPorts.Stream3;
")})));
end Stream3;


model Stream4
    connector C
        Real p;
        flow Real f;
        stream Real 's.s';
        stream Real 's.s__instream_';
    end C;
    C 'c.c';
equation
    'c.c'.p = time;
    'c.c'.'s.s' = inStream('c.c'.'s.s');
    'c.c'.'s.s__instream_' = inStream('c.c'.'s.s__instream_');
annotation(__JModelica(UnitTesting(tests={
    FlatteningTestCase(
        description="Instream variable name is already used",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream4
 potential Real 'c.c'.p;
 flow Real 'c.c'.f;
 stream Real 'c.c'.'s.s' annotation(__Modelon(internal(instream = \"'c.c'.'s.s__instream_2'\")));
 inStream Real 'c.c'.'s.s__instream_2';
 stream Real 'c.c'.'s.s__instream_' annotation(__Modelon(internal(instream = \"'c.c'.'s.s__instream___instream_'\")));
 inStream Real 'c.c'.'s.s__instream___instream_';
equation
 'c.c'.p = time;
 'c.c'.'s.s' = inStream('c.c'.'s.s');
 'c.c'.'s.s__instream_' = inStream('c.c'.'s.s__instream_');
end CausalPorts.Stream4;
"), TransformCanonicalTestCase(
        description="Instream variable name is already used",
        causal_ports=true,
        eliminate_alias_variables=false,
        variability_propagation=false,
        flatModel="
fclass CausalPorts.Stream4
 potential Real 'c.c'.p;
 flow Real 'c.c'.f;
 stream Real 'c.c'.'s.s' annotation(__Modelon(internal(instream = \"'c.c'.'s.s__instream_2'\")));
 inStream Real 'c.c'.'s.s__instream_2';
 stream Real 'c.c'.'s.s__instream_' annotation(__Modelon(internal(instream = \"'c.c'.'s.s__instream___instream_'\")));
 inStream Real 'c.c'.'s.s__instream___instream_';
equation
 'c.c'.p = time;
 'c.c'.'s.s' = 'c.c'.'s.s__instream_2';
 'c.c'.'s.s__instream_' = 'c.c'.'s.s__instream___instream_';
end CausalPorts.Stream4;
")})));
end Stream4;


end CausalPorts;
