using Xunit.Abstractions;
using Xunit.Sdk;

namespace UnitTests.Order
{
	public class RandomOrder : ITestCaseOrderer
	{
		private static readonly Random Random = new Random();

		public IEnumerable<TTestCase> OrderTestCases<TTestCase>(IEnumerable<TTestCase> testCases)
			where TTestCase : ITestCase
		{
			return testCases.OrderBy(x => Random.Next());
		}
	}
}
