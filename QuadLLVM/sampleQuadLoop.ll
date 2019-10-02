; ModuleID = 'sampleQuadLoop.cpp'
source_filename = "sampleQuadLoop.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline norecurse nounwind optnone ssp uwtable
define i32 @main() #0 !dbg !9 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4, !dbg !11
  br label %3, !dbg !12

; <label>:3:                                      ; preds = %6, %0
  %4 = load i32, i32* %2, align 4, !dbg !13
  %5 = icmp slt i32 %4, 10, !dbg !14
  br i1 %5, label %6, label %9, !dbg !12

; <label>:6:                                      ; preds = %3
  %7 = load i32, i32* %2, align 4, !dbg !15
  %8 = add nsw i32 %7, 1, !dbg !15
  store i32 %8, i32* %2, align 4, !dbg !15
  br label %3, !dbg !12, !llvm.loop !16

; <label>:9:                                      ; preds = %3
  ret i32 0, !dbg !18
}

attributes #0 = { noinline norecurse nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.dbg.cu = !{!5}
!llvm.ident = !{!8}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 14]}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{i32 7, !"PIC Level", i32 2}
!5 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !6, producer: "Apple LLVM version 10.0.1 (clang-1001.0.46.4)", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !7)
!6 = !DIFile(filename: "sampleQuadLoop.cpp", directory: "/Users/karzmac/Projects/CPPPractice")
!7 = !{}
!8 = !{!"Apple LLVM version 10.0.1 (clang-1001.0.46.4)"}
!9 = distinct !DISubprogram(name: "main", scope: !6, file: !6, line: 3, type: !10, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, unit: !5, retainedNodes: !7)
!10 = !DISubroutineType(types: !7)
!11 = !DILocation(line: 5, column: 6, scope: !9)
!12 = !DILocation(line: 6, column: 2, scope: !9)
!13 = !DILocation(line: 6, column: 10, scope: !9)
!14 = !DILocation(line: 6, column: 12, scope: !9)
!15 = !DILocation(line: 6, column: 19, scope: !9)
!16 = distinct !{!16, !12, !17}
!17 = !DILocation(line: 6, column: 21, scope: !9)
!18 = !DILocation(line: 9, column: 2, scope: !9)
