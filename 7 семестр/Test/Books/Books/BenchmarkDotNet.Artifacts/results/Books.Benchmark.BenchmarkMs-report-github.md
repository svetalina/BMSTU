```

BenchmarkDotNet v0.13.12, Windows 10 (10.0.19045.3930/22H2/2022Update)
Intel Core i3-7020U CPU 2.30GHz (Kaby Lake), 1 CPU, 4 logical and 2 physical cores
.NET SDK 7.0.302
  [Host]     : .NET 6.0.16 (6.0.1623.17311), X64 RyuJIT AVX2 [AttachedDebugger]
  DefaultJob : .NET 6.0.16 (6.0.1623.17311), X64 RyuJIT AVX2


```
| Method        | Mean     | Error     | StdDev    | Median   | Min      | Max      | Allocated |
|-------------- |---------:|----------:|----------:|---------:|---------:|---------:|----------:|
| TestGetAll    | 6.624 ms | 0.2288 ms | 0.6378 ms | 6.404 ms | 5.932 ms | 8.347 ms |  194.6 KB |
| TestGetByName | 2.924 ms | 0.1253 ms | 0.3615 ms | 2.774 ms | 2.503 ms | 4.000 ms |    9.2 KB |
