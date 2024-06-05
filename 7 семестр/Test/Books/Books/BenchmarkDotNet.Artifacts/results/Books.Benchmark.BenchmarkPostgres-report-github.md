```

BenchmarkDotNet v0.13.12, Windows 10 (10.0.19045.3930/22H2/2022Update)
Intel Core i3-7020U CPU 2.30GHz (Kaby Lake), 1 CPU, 4 logical and 2 physical cores
.NET SDK 7.0.302
  [Host]     : .NET 6.0.16 (6.0.1623.17311), X64 RyuJIT AVX2
  DefaultJob : .NET 6.0.16 (6.0.1623.17311), X64 RyuJIT AVX2


```
| Method        | Mean     | Error     | StdDev    | Median   | Min      | Max      | Gen0    | Gen1   | Allocated |
|-------------- |---------:|----------:|----------:|---------:|---------:|---------:|--------:|-------:|----------:|
| TestGetAll    | 4.450 ms | 0.1784 ms | 0.5204 ms | 4.270 ms | 3.881 ms | 5.776 ms | 23.4375 | 7.8125 | 192.49 KB |
| TestGetByName | 2.065 ms | 0.0727 ms | 0.2108 ms | 1.961 ms | 1.854 ms | 2.639 ms |       - |      - |   6.46 KB |
