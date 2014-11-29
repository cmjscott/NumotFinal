NumotFinal
==========

Numerical Methods final project
Module 3 Final Project
MECE-317, Fall 2014

You may work in groups of up to two. All projects should be submitted to the MyCourses Dropbox. You
should submit your Visual Studio project file as well as your project report. Only one report per group
needs to be submitted.
General Project Description
Create a program in C++ that simulates the velocity of a vehicle of your choice using Euler’s method.
Your program should be capable of simulating the time dependent straight line velocity of your vehicle
under specified conditions. Write the outputs of your program to MATLAB and generate plots of your
results using MATLAB plotting features.


Introduction

For this project, you will be simulating the longitudinal (straight line) acceleration of a vehicle of your
choice and calculate the velocity using Euler’s method. Lateral forces will be ignored. You should use
Newton’s Second Law (Fsum = m * a) to calculate the acceleration (a). The acceleration can then be
numerically integrated using Euler’s method
𝑣2 = 𝑣1 + 𝑑t ∗ 𝑎
to determine the velocity (v) at each time step (dt). The forces that should be included in your
simulation include a drive force (Fdrive), a drag force (Fdrag), and rolling resistance (Frr), such that
𝐹𝑠um = 𝐹drag + 𝐹drive + 𝐹rr
You will need to look up parameters of interest for your specific vehicle. In cases where you cannot find
a particular parameter, you may assume values, but should justify your choice of these parameter values
in your write-up.

Simulation 1:
Run a basic simulation that assumes a constant drive force, drag force equal to 𝐹drag = −𝐶𝑑 ∗ 𝑣^2,
and rolling resistance 𝐹𝑟𝑟 = −𝐶𝑟𝑟 ∗ 𝑣. Cdrag is the drag coefficient and may be assumed to be constant
for Simulation 1. Crr is the coefficient of rolling resistance and can be assumed to be approximately 30 *
Cdrag. Simulate the acceleration of your vehicle and determine the maximum velocity that your vehicle
can achieve for the constant drive force. Ensure that your results are independent of the time step by
modifying your time step until reductions in the time step lead to differences of less than 0.00001 in
your results.

Simulation 2:
Expand the drag force expression to include other parameters, such that 𝐹𝑑rag = 0.5 ∗ 𝐶𝑑 ∗ 𝐴 ∗ 𝑟ℎ𝑜 ∗ 𝑣^2
where A is the frontal area of the vehicle and rho is the density of air. Simulate the acceleration of your
vehicle and determine the maximum velocity that can be achieved with a more realistic simulation of
drag forces. Confirm that your simulation results are independent of the time step.

Simulation 3:
Add a term into your Fsum that simulates a linear braking force that brings the car to a stop in 10 seconds.
Simulate your vehicle accelerating to the maximum velocity in Simulation 2 then decelerating to a
complete stop.
Simulation 4:

Expand your drive force term to include the effects of engine torque (Tengine at a given RPM), gear ratio
(xg), differential ratio (xd), transmission efficiency (n - assume 70%), and the wheel radius (Rw), such that
𝐹𝑑rag = 𝑇engine ∗ 𝑥𝑔 ∗ 𝑥𝑑 ∗ 𝑛/𝑅𝑤
Simulate the acceleration of your vehicle in response to pressing the throttle from 0 to 100% over a 10
second time period. You may approximate that the torque for your vehicle is a linear function of RPM,
even if the curve you find for your vehicle is nonlinear. You should also assume that RPM is a linear
function of throttle position (0-100%). Vary the time period over which the throttle is applied to
determine the maximum velocity that can be achieved. Simulate the effect of at least one other gear
ratio for your vehicle.

For 5 points extra credit, simulate the vehicle reaching a “red line” RPM value and shifting to the next
gear until a maximum velocity is reached.


Final Report Format
The format of your report should include the following sections:
• Introduction
o Include a brief description of your vehicle and specifications (can include images).
• Methods
o Include governing equations used with all variables defined
o Include any assumptions made
o Include your COMMENTED C++ code.
• Results
o Include your simulation results with a description of what the results show
o All graphs should be clearly labeled and a description provided. It is not sufficient to just
include graphs with captions! There must be text explaining the graphs. • Analysis
o This section should include an overall discussion of what you observed from your
simulation results and how realistic your results were.
o Discuss how the refinements to the model impacted your simulation results as well as
how assumptions may have limited the accuracy of your results.
o Include a discussion of how the simulation results could be improved
• Conclusions
o Conclude with 1-2 paragraphs that tie the results and analysis together.
