using LibWorkBench.Core.Models.Details;
using LibWorkBench.IO.Streams;

namespace LibWorkBenchTests.Integrity.Details
{
    /// <summary>
    /// Base class for integrity tests
    /// </summary>
    /// <typeparam name="TResource">Resource class type</typeparam>
    /// <typeparam name="TTestFile">Test file class type</typeparam>
    public abstract class IntegrityTestImpl<TResource, TTestFile>
        where TResource : ResourceImpl, new()
        where TTestFile : TestFile
    {
        /// <summary>
        /// Performs any logic necessary before running the current test
        /// </summary>
        /// <param name="resource">WorkBench resource</param>
        /// <param name="file">Test case file</param>
        public virtual void BeforeTest(TResource resource, TTestFile file)
        {
        }

        /// <summary>
        /// Performs any logic necessary after running the current test
        /// </summary>
        /// <param name="resource">WorkBench resource</param>
        /// <param name="file">Test case file</param>
        public virtual void AfterTest(TResource resource, TTestFile file)
        {
        }

        /// <summary>
        /// Runs through the provided list of test case files
        /// </summary>
        /// <param name="files">Test case files</param>
        public void Run(List<TestFile> files)
        {
            foreach (var it in files)
            {
                TTestFile test = (TTestFile)it;

                // Test artifact paths
                string binaryPath = $"{it.Path}.testbin";
                string jsonPath = $"{it.Path}.testjson";

                // Encoding test (JSON -> binary)
                {
                    TResource resource = new();
                    BeforeTest(resource, test);

                    // JSON decode
                    using (JsonFileReader reader = new(it.Path))
                    {
                        resource.Load(reader);
                    }

                    // Binary encode
                    using (BinaryFileWriter writer = new(binaryPath, it.Endian))
                    {
                        resource.Write(writer);
                    }

                    Assert.AreEqual(
                        it.Hash,
                        IntegrityUtil.GetSha256Hash(binaryPath),
                        ignoreCase: true,
                        message: $"Binary encoding is wrong: {it.Path}"
                    );

                    AfterTest(resource, test);
                }

                // Decoding test (binary -> JSON -> binary)
                {
                    TResource resource = new();
                    BeforeTest(resource, test);

                    // Binary decode
                    using (BinaryFileReader reader = new(binaryPath, it.Endian))
                    {
                        resource.Read(reader);
                    }

                    // JSON encode
                    using (JsonFileWriter writer = new(jsonPath))
                    {
                        resource.Dump(writer);
                    }

                    // JSON decode
                    using (JsonFileReader reader = new(jsonPath))
                    {
                        resource.Load(reader);
                    }

                    // Binary encode
                    using (BinaryFileWriter writer = new(binaryPath, it.Endian))
                    {
                        resource.Write(writer);
                    }

                    Assert.AreEqual(
                        it.Hash,
                        IntegrityUtil.GetSha256Hash(binaryPath),
                        ignoreCase: true,
                        message: $"Binary encoding is wrong: {it.Path}"
                    );

                    AfterTest(resource, test);
                }
            }
        }
    }
}
