; ModuleID = 'main'
source_filename = "main"

@.str = private constant [19 x i8] c"function call: %d\0A\00"
@.str.1 = private constant [6 x i8] c"asdfs\00"
@.str.2 = private constant [7 x i8] c"Equal\0A\00"
@.str.3 = private constant [11 x i8] c"Not Equal\0A\00"
@.str.4 = private constant [3 x i8] c"%d\00"
@.str.5 = private constant [2 x i8] c"\0A\00"
@.str.6 = private constant [3 x i8] c"%d\00"
@.str.7 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(i8*, ...)

define i32 @add(i32 %a1, i32 %d2) {
entry:
  %a = alloca i32
  store i32 %a1, i32* %a
  %d = alloca i32
  store i32 %d2, i32* %d
  %0 = load i32, i32* %a
  %1 = load i32, i32* %d
  %2 = add i32 %0, %1
  ret i32 %2
}

define i32 @main() {
entry:
  %0 = call i32 @add(i32 1, i32 2)
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i32 %0)
  %a = alloca i8*
  %2 = load i8*, i8** %a
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8** %a
  %i = alloca i32
  %3 = load i32, i32* %i
  store i32 3, i32* %i
  %j = alloca i32
  %4 = load i32, i32* %j
  store i32 4, i32* %j
  %5 = load i32, i32* %j
  %6 = load i32, i32* %i
  %7 = icmp eq i32 %6, %5
  %8 = xor i1 %7, true
  br i1 %8, label %then, label %else

then:                                             ; preds = %entry
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0))
  br label %cont

else:                                             ; preds = %entry
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0))
  br label %cont

cont:                                             ; preds = %else, %then
  %k = alloca i32
  %11 = load i32, i32* %k
  store i32 3, i32* %k
  br label %cond

cond:                                             ; preds = %progress, %cont
  %12 = load i32, i32* %k
  %13 = icmp slt i32 %12, 10
  br i1 %13, label %loop, label %after

loop:                                             ; preds = %cond
  %14 = load i32, i32* %k
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0), i32 %14)
  br label %progress

progress:                                         ; preds = %loop
  %16 = load i32, i32* %k
  %17 = add i32 %16, 1
  store i32 %17, i32* %k
  br label %cond

after:                                            ; preds = %cond
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0))
  %k1 = alloca i32
  %19 = load i32, i32* %k1
  store i32 3, i32* %k1
  br label %whlcond2

whlcond2:                                         ; preds = %whlloop, %after
  %20 = load i32, i32* %k1
  %21 = icmp slt i32 %20, 7
  br i1 %21, label %whlloop, label %whlafter

whlloop:                                          ; preds = %whlcond2
  %22 = load i32, i32* %k1
  %23 = add i32 %22, 1
  store i32 %23, i32* %k1
  %24 = load i32, i32* %k1
  %25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.6, i32 0, i32 0), i32 %24)
  br label %whlcond2

whlafter:                                         ; preds = %whlcond2
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i32 0, i32 0))
  ret i32 0
}
