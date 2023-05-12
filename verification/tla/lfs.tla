---- MODULE lfs ----

EXTENDS Sequences, Integers, TLC

(*--algorithm lfs

variables
    stack_var = <<>>,
    memory_order_seq_lock = 0,

define
    NoRaceCondition == memory_order_seq_lock <= 1
    EmptyOnExit == Len(stack_var) = 0
end define;

process worker \in 1..5
variables
    head_push = "",
    head_pop = "",

begin
push1:
    await memory_order_seq_lock = 0;
    memory_order_seq_lock := memory_order_seq_lock + 1;
    if stack_var = <<>> then
        stack_var := Append(stack_var, Len(stack_var));
        goto push_unlock2;
    else
        head_push := Head(stack_var);
    end if;

push_unlock1:
    memory_order_seq_lock := memory_order_seq_lock - 1;

push2:
    await memory_order_seq_lock = 0;
    
    if stack_var = <<>> then
        goto push1;
    else
        if head_push = Head(stack_var) then
            memory_order_seq_lock := memory_order_seq_lock + 1;
            stack_var := Append(stack_var, Len(stack_var));
        else
            goto push2;
        end if;
    end if;

push_unlock2:
    memory_order_seq_lock := memory_order_seq_lock - 1;

pop1:
    await memory_order_seq_lock = 0;
    memory_order_seq_lock := memory_order_seq_lock + 1;
    if stack_var = <<>> then
        goto pop_unlock2;
    else
        head_pop := Head(stack_var);
    end if;

pop_unlock1:
    memory_order_seq_lock := memory_order_seq_lock - 1;   

pop2:
    await memory_order_seq_lock = 0;
    if stack_var = <<>> then
        goto pop1;
    else
        if head_pop = Head(stack_var) then
            memory_order_seq_lock := memory_order_seq_lock + 1;
            stack_var := SubSeq(stack_var, 1, Len(stack_var)-1);
        else
            goto pop2;
        end if;
    end if;

pop_unlock2:
    memory_order_seq_lock := memory_order_seq_lock - 1;

end process;

end algorithm;*)
===================================
