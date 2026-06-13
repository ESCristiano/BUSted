.syntax unified 
// ----------------- Block Jumps of Cache Size ----------------- 
#.section covert, "ax", %progbits 
.balign (64*16)
.globl block_jumps_0_0
.globl block_bx_lr_way_0

block_bx_lr_way_0:
	bx lr
block_jumps_0_0:
	push {lr}
	bl block_bx_lr_last_way
	b  block_jumps_0_1

.balign (16)
block_bx_lr_way_0_1:
	bx lr
block_jumps_0_1:
	bl block_bx_lr_last_way_1
	b  block_jumps_0_2

.balign (16)
block_bx_lr_way_0_2:
	bx lr
block_jumps_0_2:
	bl block_bx_lr_last_way_2
	b  block_jumps_0_3

.balign (16)
block_bx_lr_way_0_3:
	bx lr
block_jumps_0_3:
	bl block_bx_lr_last_way_3
	b  block_jumps_0_4

.balign (16)
block_bx_lr_way_0_4:
	bx lr
block_jumps_0_4:
	bl block_bx_lr_last_way_4
	b  block_jumps_0_5

.balign (16)
block_bx_lr_way_0_5:
	bx lr
block_jumps_0_5:
	bl block_bx_lr_last_way_5
	b  block_jumps_0_6

.balign (16)
block_bx_lr_way_0_6:
	bx lr
block_jumps_0_6:
	bl block_bx_lr_last_way_6
	b  block_jumps_0_7

.balign (16)
block_bx_lr_way_0_7:
	bx lr
block_jumps_0_7:
	bl block_bx_lr_last_way_7
	b  block_jumps_0_8

.balign (16)
block_bx_lr_way_0_8:
	bx lr
block_jumps_0_8:
	bl block_bx_lr_last_way_8
	b  block_jumps_0_9

.balign (16)
block_bx_lr_way_0_9:
	bx lr
block_jumps_0_9:
	bl block_bx_lr_last_way_9
	b  block_jumps_0_10

.balign (16)
block_bx_lr_way_0_10:
	bx lr
block_jumps_0_10:
	bl block_bx_lr_last_way_10
	b  block_jumps_0_11

.balign (16)
block_bx_lr_way_0_11:
	bx lr
block_jumps_0_11:
	bl block_bx_lr_last_way_11
	b  block_jumps_0_12

.balign (16)
block_bx_lr_way_0_12:
	bx lr
block_jumps_0_12:
	bl block_bx_lr_last_way_12
	b  block_jumps_0_13

.balign (16)
block_bx_lr_way_0_13:
	bx lr
block_jumps_0_13:
	bl block_bx_lr_last_way_13
	b  block_jumps_0_14

.balign (16)
block_bx_lr_way_0_14:
	bx lr
block_jumps_0_14:
	bl block_bx_lr_last_way_14
	b  block_jumps_0_15

.balign (16)
block_bx_lr_way_0_15:
	bx lr
block_jumps_0_15:
	bl block_bx_lr_last_way_15
	b  block_jumps_0_16

.balign (16)
block_bx_lr_way_0_16:
	bx lr
block_jumps_0_16:
	bl block_bx_lr_last_way_16
	b  block_jumps_0_17

.balign (16)
block_bx_lr_way_0_17:
	bx lr
block_jumps_0_17:
	bl block_bx_lr_last_way_17
	b  block_jumps_0_18

.balign (16)
block_bx_lr_way_0_18:
	bx lr
block_jumps_0_18:
	bl block_bx_lr_last_way_18
	b  block_jumps_0_19

.balign (16)
block_bx_lr_way_0_19:
	bx lr
block_jumps_0_19:
	bl block_bx_lr_last_way_19
	b  block_jumps_0_20

.balign (16)
block_bx_lr_way_0_20:
	bx lr
block_jumps_0_20:
	bl block_bx_lr_last_way_20
	b  block_jumps_0_21

.balign (16)
block_bx_lr_way_0_21:
	bx lr
block_jumps_0_21:
	bl block_bx_lr_last_way_21
	b  block_jumps_0_22

.balign (16)
block_bx_lr_way_0_22:
	bx lr
block_jumps_0_22:
	bl block_bx_lr_last_way_22
	b  block_jumps_0_23

.balign (16)
block_bx_lr_way_0_23:
	bx lr
block_jumps_0_23:
	bl block_bx_lr_last_way_23
	b  block_jumps_0_24

.balign (16)
block_bx_lr_way_0_24:
	bx lr
block_jumps_0_24:
	bl block_bx_lr_last_way_24
	b  block_jumps_0_25

.balign (16)
block_bx_lr_way_0_25:
	bx lr
block_jumps_0_25:
	bl block_bx_lr_last_way_25
	b  block_jumps_0_26

.balign (16)
block_bx_lr_way_0_26:
	bx lr
block_jumps_0_26:
	bl block_bx_lr_last_way_26
	b  block_jumps_0_27

.balign (16)
block_bx_lr_way_0_27:
	bx lr
block_jumps_0_27:
	bl block_bx_lr_last_way_27
	b  block_jumps_0_28

.balign (16)
block_bx_lr_way_0_28:
	bx lr
block_jumps_0_28:
	bl block_bx_lr_last_way_28
	b  block_jumps_0_29

.balign (16)
block_bx_lr_way_0_29:
	bx lr
block_jumps_0_29:
	bl block_bx_lr_last_way_29
	b  block_jumps_0_30

.balign (16)
block_bx_lr_way_0_30:
	bx lr
block_jumps_0_30:
	bl block_bx_lr_last_way_30
	b  block_jumps_0_31

.balign (16)
block_bx_lr_way_0_31:
	bx lr
block_jumps_0_31:
	bl block_bx_lr_last_way_31
	b  block_jumps_0_32

.balign (16)
block_bx_lr_way_0_32:
	bx lr
block_jumps_0_32:
	bl block_bx_lr_last_way_32
	b  block_jumps_0_33

.balign (16)
block_bx_lr_way_0_33:
	bx lr
block_jumps_0_33:
	bl block_bx_lr_last_way_33
	b  block_jumps_0_34

.balign (16)
block_bx_lr_way_0_34:
	bx lr
block_jumps_0_34:
	bl block_bx_lr_last_way_34
	b  block_jumps_0_35

.balign (16)
block_bx_lr_way_0_35:
	bx lr
block_jumps_0_35:
	bl block_bx_lr_last_way_35
	b  block_jumps_0_36

.balign (16)
block_bx_lr_way_0_36:
	bx lr
block_jumps_0_36:
	bl block_bx_lr_last_way_36
	b  block_jumps_0_37

.balign (16)
block_bx_lr_way_0_37:
	bx lr
block_jumps_0_37:
	bl block_bx_lr_last_way_37
	b  block_jumps_0_38

.balign (16)
block_bx_lr_way_0_38:
	bx lr
block_jumps_0_38:
	bl block_bx_lr_last_way_38
	b  block_jumps_0_39

.balign (16)
block_bx_lr_way_0_39:
	bx lr
block_jumps_0_39:
	bl block_bx_lr_last_way_39
	b  block_jumps_0_40

.balign (16)
block_bx_lr_way_0_40:
	bx lr
block_jumps_0_40:
	bl block_bx_lr_last_way_40
	b  block_jumps_0_41

.balign (16)
block_bx_lr_way_0_41:
	bx lr
block_jumps_0_41:
	bl block_bx_lr_last_way_41
	b  block_jumps_0_42

.balign (16)
block_bx_lr_way_0_42:
	bx lr
block_jumps_0_42:
	bl block_bx_lr_last_way_42
	b  block_jumps_0_43

.balign (16)
block_bx_lr_way_0_43:
	bx lr
block_jumps_0_43:
	bl block_bx_lr_last_way_43
	b  block_jumps_0_44

.balign (16)
block_bx_lr_way_0_44:
	bx lr
block_jumps_0_44:
	bl block_bx_lr_last_way_44
	b  block_jumps_0_45

.balign (16)
block_bx_lr_way_0_45:
	bx lr
block_jumps_0_45:
	bl block_bx_lr_last_way_45
	b  block_jumps_0_46

.balign (16)
block_bx_lr_way_0_46:
	bx lr
block_jumps_0_46:
	bl block_bx_lr_last_way_46
	b  block_jumps_0_47

.balign (16)
block_bx_lr_way_0_47:
	bx lr
block_jumps_0_47:
	bl block_bx_lr_last_way_47
	b  block_jumps_0_48

.balign (16)
block_bx_lr_way_0_48:
	bx lr
block_jumps_0_48:
	bl block_bx_lr_last_way_48
	b  block_jumps_0_49

.balign (16)
block_bx_lr_way_0_49:
	bx lr
block_jumps_0_49:
	bl block_bx_lr_last_way_49
	b  block_jumps_0_50

.balign (16)
block_bx_lr_way_0_50:
	bx lr
block_jumps_0_50:
	bl block_bx_lr_last_way_50
	b  block_jumps_0_51

.balign (16)
block_bx_lr_way_0_51:
	bx lr
block_jumps_0_51:
	bl block_bx_lr_last_way_51
	b  block_jumps_0_52

.balign (16)
block_bx_lr_way_0_52:
	bx lr
block_jumps_0_52:
	bl block_bx_lr_last_way_52
	b  block_jumps_0_53

.balign (16)
block_bx_lr_way_0_53:
	bx lr
block_jumps_0_53:
	bl block_bx_lr_last_way_53
	b  block_jumps_0_54

.balign (16)
block_bx_lr_way_0_54:
	bx lr
block_jumps_0_54:
	bl block_bx_lr_last_way_54
	b  block_jumps_0_55

.balign (16)
block_bx_lr_way_0_55:
	bx lr
block_jumps_0_55:
	bl block_bx_lr_last_way_55
	b  block_jumps_0_56

.balign (16)
block_bx_lr_way_0_56:
	bx lr
block_jumps_0_56:
	bl block_bx_lr_last_way_56
	b  block_jumps_0_57

.balign (16)
block_bx_lr_way_0_57:
	bx lr
block_jumps_0_57:
	bl block_bx_lr_last_way_57
	b  block_jumps_0_58

.balign (16)
block_bx_lr_way_0_58:
	bx lr
block_jumps_0_58:
	bl block_bx_lr_last_way_58
	b  block_jumps_0_59

.balign (16)
block_bx_lr_way_0_59:
	bx lr
block_jumps_0_59:
	bl block_bx_lr_last_way_59
	b  block_jumps_0_60

.balign (16)
block_bx_lr_way_0_60:
	bx lr
block_jumps_0_60:
	bl block_bx_lr_last_way_60
	b  block_jumps_0_61

.balign (16)
block_bx_lr_way_0_61:
	bx lr
block_jumps_0_61:
	bl block_bx_lr_last_way_61
	b  block_jumps_0_62

.balign (16)
block_bx_lr_way_0_62:
	bx lr
block_jumps_0_62:
	bl block_bx_lr_last_way_62
	b  block_jumps_0_63

.balign (16)
block_bx_lr_way_0_63:
	bx lr
block_jumps_0_63:
	bl block_bx_lr_last_way_63
	pop {lr}
	bx lr

// ----------------- Block of bx lr ----------------- 
.balign (64*16)
.globl block_bx_lr_last_way

block_bx_lr_last_way:
	bx lr 

.balign (16)
block_bx_lr_last_way_1:
	bx lr 

.balign (16)
block_bx_lr_last_way_2:
	bx lr 

.balign (16)
block_bx_lr_last_way_3:
	bx lr 

.balign (16)
block_bx_lr_last_way_4:
	bx lr 

.balign (16)
block_bx_lr_last_way_5:
	bx lr 

.balign (16)
block_bx_lr_last_way_6:
	bx lr 

.balign (16)
block_bx_lr_last_way_7:
	bx lr 

.balign (16)
block_bx_lr_last_way_8:
	bx lr 

.balign (16)
block_bx_lr_last_way_9:
	bx lr 

.balign (16)
block_bx_lr_last_way_10:
	bx lr 

.balign (16)
block_bx_lr_last_way_11:
	bx lr 

.balign (16)
block_bx_lr_last_way_12:
	bx lr 

.balign (16)
block_bx_lr_last_way_13:
	bx lr 

.balign (16)
block_bx_lr_last_way_14:
	bx lr 

.balign (16)
block_bx_lr_last_way_15:
	bx lr 

.balign (16)
block_bx_lr_last_way_16:
	bx lr 

.balign (16)
block_bx_lr_last_way_17:
	bx lr 

.balign (16)
block_bx_lr_last_way_18:
	bx lr 

.balign (16)
block_bx_lr_last_way_19:
	bx lr 

.balign (16)
block_bx_lr_last_way_20:
	bx lr 

.balign (16)
block_bx_lr_last_way_21:
	bx lr 

.balign (16)
block_bx_lr_last_way_22:
	bx lr 

.balign (16)
block_bx_lr_last_way_23:
	bx lr 

.balign (16)
block_bx_lr_last_way_24:
	bx lr 

.balign (16)
block_bx_lr_last_way_25:
	bx lr 

.balign (16)
block_bx_lr_last_way_26:
	bx lr 

.balign (16)
block_bx_lr_last_way_27:
	bx lr 

.balign (16)
block_bx_lr_last_way_28:
	bx lr 

.balign (16)
block_bx_lr_last_way_29:
	bx lr 

.balign (16)
block_bx_lr_last_way_30:
	bx lr 

.balign (16)
block_bx_lr_last_way_31:
	bx lr 

.balign (16)
block_bx_lr_last_way_32:
	bx lr 

.balign (16)
block_bx_lr_last_way_33:
	bx lr 

.balign (16)
block_bx_lr_last_way_34:
	bx lr 

.balign (16)
block_bx_lr_last_way_35:
	bx lr 

.balign (16)
block_bx_lr_last_way_36:
	bx lr 

.balign (16)
block_bx_lr_last_way_37:
	bx lr 

.balign (16)
block_bx_lr_last_way_38:
	bx lr 

.balign (16)
block_bx_lr_last_way_39:
	bx lr 

.balign (16)
block_bx_lr_last_way_40:
	bx lr 

.balign (16)
block_bx_lr_last_way_41:
	bx lr 

.balign (16)
block_bx_lr_last_way_42:
	bx lr 

.balign (16)
block_bx_lr_last_way_43:
	bx lr 

.balign (16)
block_bx_lr_last_way_44:
	bx lr 

.balign (16)
block_bx_lr_last_way_45:
	bx lr 

.balign (16)
block_bx_lr_last_way_46:
	bx lr 

.balign (16)
block_bx_lr_last_way_47:
	bx lr 

.balign (16)
block_bx_lr_last_way_48:
	bx lr 

.balign (16)
block_bx_lr_last_way_49:
	bx lr 

.balign (16)
block_bx_lr_last_way_50:
	bx lr 

.balign (16)
block_bx_lr_last_way_51:
	bx lr 

.balign (16)
block_bx_lr_last_way_52:
	bx lr 

.balign (16)
block_bx_lr_last_way_53:
	bx lr 

.balign (16)
block_bx_lr_last_way_54:
	bx lr 

.balign (16)
block_bx_lr_last_way_55:
	bx lr 

.balign (16)
block_bx_lr_last_way_56:
	bx lr 

.balign (16)
block_bx_lr_last_way_57:
	bx lr 

.balign (16)
block_bx_lr_last_way_58:
	bx lr 

.balign (16)
block_bx_lr_last_way_59:
	bx lr 

.balign (16)
block_bx_lr_last_way_60:
	bx lr 

.balign (16)
block_bx_lr_last_way_61:
	bx lr 

.balign (16)
block_bx_lr_last_way_62:
	bx lr 

.balign (16)
block_bx_lr_last_way_63:
	bx lr 

