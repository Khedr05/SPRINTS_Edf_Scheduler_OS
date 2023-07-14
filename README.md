# SPRINTS_Earliest_Deadline_First_Os_Scheduling_Algo
![time-now-hourglass-wallpaper-preview](https://github.com/Soliman162/EDF_Scheduler_Based_on_freeRTOS/assets/60091384/39f2d28c-b3da-48ac-b45d-a0a48a8798b4)



## Graduation Project
### Brief
> - Earliest Deadline First (EDF) is a scheduling algorithm that adopts a dynamic priority-based preemptive scheduling policy, meaning that the priority of a task can change during its execution, and the processing of any task is interrupted by a request for any higher priority task.
### Aims of the project
> - As we saw, FreeRTOS uses a static scheduler where tasks are given a fixed priority.
    The goal of this project is to implement a new dynamic priority scheduler algorithms for
    FreeRTOS: which is based on the well-known Earliest Deadline First algorithm (EDF).

#### Author: Team_5

|     Members    | 🔗 [GitHub] Links                   |
|----------------|-------------------------------------|
|     Sherif     | (https://github.com/sherifkhadr)    |
|     Sharpel    | (https://github.com/sharpelmalak)   |
|     Moamen     | (https://github.com/MomenHassan12)  |
|     Atef       | (https://github.com/ahmedatef1496)  |
|     Mowafey    | (https://github.com/Mahmoud-Mowafy) |


## Documentation
> - `Project Documentation`
    [PDF](https://github.com/sherifkhadr/SPRINTS_Edf_Scheduler_OS/tree/delivery_branch/02_Documentation)
> - `Team Backlog`
    [Google Sheets]()
    [PDF]()
> - `Test Protocol`
    [Google Sheets]()
    [PDF]()
> - `Video & Simulation_Test`
    [Videos]()
> - ---





#### System Requirement Specifications
    1.Read a thesis and implement the required changes
        This thesis discusses how to implement an EDF scheduler using FreeRTOS
        Read Chapter 2: "FreeRTOS Task Scheduling". This is an important chapter to build a profound base before starting the project
        Read Chapter 3: "EDF Scheduler". This chapter is the main chapter you will use to implement the EDF scheduler using FreeRTOS
        Implement the changes mentioned in Chapter 3.2.2: "Implementation in FreeRTOS". The changes will be implemented in tasks.c source file only
    2.Implement the missing changes from the thesis
        In order for the EDF scheduler to work correctly, you still need to implement some changes that are not mentioned in the thesis:
        In the “prvIdleTask” function, modify the idle task to keep it always the farthest deadline
        In the "xTaskIncrementTick" function, in every tick increment, calculate the new task deadline and insert it in the correct position in the EDF ready list
        In the "xTaskIncrementTick" function, make sure that as soon as a new task is available in the EDF ready list, a context switching should take place. Modify preemption way as any task with a sooner deadline must preempt a task with a larger deadline instead of a priority        
    3. Implement 4 tasks using the EDF scheduler
        In order to verify the EDF scheduler, you need to implement an application:
        Create 4 tasks with the following criteria:
        Task 1: “Button_1_Monitor”, {Periodicity: 50, Deadline: 50}, this task will monitor the rising and falling edge on button 1 and send this event to the consumer task. (Note: The rising and falling edges are treated as separate events, hence they have separate strings)
        Task 2: “Button_2_Monitor”, {Periodicity: 50, Deadline: 50}, this task will monitor the rising and falling edge on button 2 and send this event to the consumer task. (Note: The rising and falling edges are treated as separate events, hence they have separate strings)
        Task 3: "Periodic_Transmitter", {Periodicity: 100, Deadline: 100}, this task will send periodic string every 100ms to the consumer task
        Task 4: "Uart_Receiver", {Periodicity: 20, Deadline: 20}, this is the consumer task which will write on UART any received string from other tasks
        Add the 5th and 6th tasks to simulate a heavier load:
        Task 5: “Load_1_Simulation”, {Periodicity: 10, Deadline: 10}, Execution time: 5ms
        Task 6: “Load_2_Simulation”, {Periodicity: 100, Deadline: 100}, Execution time: 12ms
        These two tasks shall be implemented as an empty loop that loops X times. You shall determine the X times to achieve the required execution time mentioned above. (Hint: In run-time use GPIOs and a logic analyzer to determine the execution time)
        Implement all the tasks mentioned above in the same main.c source file
    4.Verifying the system implementation
        Now you should verify your system implementation with the EDF scheduler using the following methods:
        Using analytical methods calculate the following for the given set of tasks:
        Calculate the system hyper-period
        Calculate the CPU load
        Check system schedulability using URM and time demand analysis techniques (Assuming the given set of tasks are scheduled using a fixed priority rate -monotonic scheduler)
        Note: For all the tasks you should calculate the execution time from the actual implemented tasks using GPIOs and the logic analyzer
        Using Simso offline simulator, simulate the given set of tasks assuming:
        Fixed priority rate monotonic scheduler
        Using the Keil simulator in run-time and the given set of tasks:
        Calculate the CPU usage time using timer 1 and trace macros
        Using trace macros and GPIOs, plot the execution of all tasks, tick, and the idle task on the logic analyzer
    5.Optional Requirements
        When implementing the missing changes from the thesis, modify the function to read the tasks status from the EDF ready list in the "uxTaskGetSystemState" function
        When you are Verifying the system implementation, use FreeRTOS run-time stats function "uxTaskGetSystemState", and print the stats summary of all tasks
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Environment used
> - 




