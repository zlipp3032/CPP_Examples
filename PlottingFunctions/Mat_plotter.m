% Plotting function for .cpp simulations

close all
clear
clc


A = readtable("simulation_data.csv");


startTime = A.T_Kutta(1);
endTime = A.T_Kutta(end);

figure
subplot(2,1,1)
plot(A.T_Kutta,A.pos_1,'b')
hold on
plot(A.T_Kutta,A.pos_2,'r')
plot(A.T_Kutta,A.Leader_Pos,'k--')
hold off
grid on
ylabel('$q_i$~(m)','interpreter','latex')
xlim([startTime endTime])
set(gca,'xticklabel',[])

subplot(2,1,2)
plot(A.T_Kutta,A.vel_1,'b')
hold on
plot(A.T_Kutta,A.vel_2,'r')
plot(A.T_Kutta,A.Leader_Vel,'k--')
hold off
grid on
xlabel('$t$~(s)','interpreter','latex')
ylabel('$p_i$~(m/s)','interpreter','latex')
xlim([startTime endTime])