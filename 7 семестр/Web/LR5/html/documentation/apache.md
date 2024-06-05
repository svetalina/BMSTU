# Результаты нагрузочного тестирования

**Server Software:** Books

**Server Hostname:** localhost

**Server Port:** 80


**Document Path:** /api/v1/search?name=1984

**Document Length:** 175 bytes


**Concurrency Level:** 1

**Time taken for tests:** 14.997 seconds

**Complete requests:** 1000

**Failed requests:** 0

**Total transferred:** 312000 bytes

**HTML transferred:** 175000 bytes

**Requests per second:** 66.68 [#/sec] (mean)

**Time per request:** 14.997 [ms] (mean)

**Time per request:** 14.997 [ms] (mean, across all concurrent requests)

**Transfer rate:** 20.32 [Kbytes/sec] received

## Connection Times (ms)
|              | min | mean     | +/-sd | median | max   |
|--------------|-----|----------|-------|--------|-------|
| Connect:     | 0   | 0        | 0.5   | 0      | 2     |
| Processing:  | 0   | 12       | 328.3 | 2      | 10384 |
| Waiting:     | 0   | 12       | 328.2 | 1      | 10381 |
| Total:       | 1   | 13       | 328.3 | 2      | 10385 |

## Percentage of the requests served within a certain time (ms)
| 50%   | 66%   | 75%   | 80%   | 90%   | 95%   | 98%   | 99%   | 100%   |
|-------|-------|-------|-------|-------|-------|-------|-------|--------|
| 2     | 2     | 3     | 3     | 4     | 4     | 5     | 5     | 10385  |
