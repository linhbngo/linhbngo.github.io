---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Testing"
toc:
  - name: Style Guides
  - name: Portability
  - name: Testing
  - name: Dynamic analysis
---
# Testing

## Style Guides

{% details Style automation %}

- Enforce adherence to coding styles according to predefined guilines
- Example: [Prettier.io](https://prettier.io/playground/)
- Advantages
    - Zero human effort
    - Uniform enforcement
    - Prevent accidentally misleading style
    - Can be applied after refactoring, synthesizing code
    - Can update entire codebase when style rules change
- Disadvantages
    - Can't reproduce all reasonable style rules    
    - Special-case exceptions are awkward
    - Reformatting pollutes blame history

{% enddetails %}
{% details Style guide examples %}

- Examples
    - [Google: C++](https://google.github.io/styleguide/cppguide.html)
    - [Google: Java](https://google.github.io/styleguide/javaguide.html)
    - [Google: Python](https://google.github.io/styleguide/pyguide.html)
- Don't blindly adopt someone else's style guide 
    – Some justifications may not apply externally
    - But good to inherit from
- Elements of good style guides
    - Justify choices
        - Avoid danger
        - Enforce best practice
        - Ensure consistency
    - Avoid details that can be automated
    - Get developer buy-in

{% enddetails %}
## Portability

{% details Advantages and Drawbacks %}

- Advantages
    - Enlarges customer base
    - Futureproofing
        - e.g. Apple Silicon
    - Reduces implicit assumptions
    - Improves process robustness
    - Expands tooling options
        - Compilers
        - Analysis tools
    - Educates team
- Example anecdote: Every time I build a project with a new 
compiler, I discover bugs
    - Sometimes those bugs are in the compiler... but most 
    are in the application
- Drawbacks
    - Maintenance burden

{% enddetails %}
{% details Portability targets %}

- Architecture
    - x86, ARM, 32 vs. 64-bit
- Operating system
    - Linux (Red Hat, Debian), Windows, Mac OS
    - Android, iOS
- Form factor
    - Smatphone, tablet, laptop, desktop, dual monitors
- Web browser
    - Chrome, Safari, Firefox
- C/C++ compilers
    - GCC, Clang, MSVC, Intel, Solaris Studio, IBM XL, PGI, SGI/Open64/PathScale
- Java virtual machines
    - Oracle/OpenJDK, IBM/OpenJ9, Azul
- Python interpreters
    - CPython, PyPy, Jython

{% enddetails %}
{% details Techniques to improve portability %}

- Heterogeneous developer environments
- Automated cross-platform builds and tests
    - Cloud infrastructure available
    - Don't ignore errors
- Highlight in style guides, code review checklists
- Use cross-platform standards and abstraction layers
    - Avoid writing your own #ifdefs unless portability is a business case
- Common gotchas:
    - Integer sizes
    - Filesystems
    - Unsupported APIs, language features
    - Floating-point behavior
    - Performance characteristics
    - Assumptions about unspecified behavior

{% enddetails %}
## Testing

{% details Goals of testing %}

- Find and prevent bugs
- Improve maintainability (esp. refactoring)
- Clarify intended usage
- To meet these goals, tests themselves should be:
    - Bug-free
    - Maintainable
    - Clearly documented and easy to read

{% enddetails %}
{% details Test coverage %}

- Ways to measure "how much
code" was tested
    - Function coverage
    - Statement (line) coverage
    - Branch coverage
    - Condition/decision coverage
    - Loop coverage
    - Path coverage
    - ...
- Coverage analysis can reveal
gaps in testing
{% details Identify test cases to cover the following snippet of code %}

```java
if (a>b && c!=25) { 
    d++; 
}
```
{% details Solution %}

- Required cases for condition/decision coverage:
    - `a<=b`  
    - `a>b && c==25`
    - `a>b && c!=25`

{% enddetails %}
{% enddetails %}
{% enddetails %}
{% details Coverage targets %}

- Any statement not covered by a test is code you expect
your client/users to run before you do
- By this philosophy, 100% line coverage would be a minimum target
- But chasing coverage metrics with low-quality tests can be self-defeating
- Tests take time to write, review, and run; must consider cost/benefit ratio

{% enddetails %}
{% details Discussion: difficult testing scenarios %}

- Discuss the following testing scenarios
    - Error codes & exceptions from library and system calls
        - Out of memory
        - Out of disk space
        - Incomplete I/O
        - Transient I/O error (EAGAIN)
        - Timeouts
    - Unbounded blocking
    - Crash/power loss
        - Corrupted data
    - Malicious intent
    - Concurrency
        - High lock contention
        - Race conditions
        - Caching & memory ordering
        - True concurrency vs. multitasking
    - Portability
        - Unsupported capabilities
        - Platform differences
    - Performance
        - NUMA
        - Big.LITTLE
        - Disk I/O (bandwidth, latency)
        - Network I/O (bandwidth, latency)

{% enddetails %}
{% details Beyoncé rule %}

- "If you liked it, then you shoulda put a test on it"
- Manages responsibility during large-scale refactoring
    - Infrastructure team must ensure all tests pass before committing
    - If functionality breaks, product team must fix it (and add more tests)
- Aim for sufficient coverage so that you (and your teammates) would
be okay being held responsible for a production breakage in
uncovered code

{% enddetails %}
{% details SQLite %}

- https://www.sqlite.org/testing.html
- 640x more test code than application code
- 100% branch test coverage
- OOM, I/O errors, crashes
    - Use abstractions to wrap malloc, I/O operations
- Boundary values
- Regression tests
- Valgrind
- Fuzz testing

{% enddetails %}
{% details Kinds of testing %}

- Styles
    - Exploratory: unscripted testing done by the developers themselves
    - Smoke tests: minimal attempts to operate the software to identify basic problems
    - Black box: test development without knowledge of the implementation/source code
    - Glass box: formal verification of a program's internal structure/workflow
    - Fuzzy testing: a type of blackbox testing that involves invalid/unexpected/random data. 
    - Dynamic analysis: evaluate software behavior during run time. 
- Scopes
    - Unit tests
    - Integration tests
    - End-to-end tests
- Sizes
    - Small: fast, deterministic (in-process)
    - Medium: multi-process, allow blocking calls (single machine)
    - Large: Multi-node
- Purpose
    - Prevent reoccurrence of bugs (regression tests)
    - Prepare for release (acceptance tests, beta testing)
    - Ensure operating health (self tests)

{% enddetails %}
{% details Aerospace testing %}

- Unit tests
    - Ensure thorough coverage
    - Verify independent implementations
- Smoke tests
    - Small-scale integration test
    - Ensure configs are valid
- Regression tests
    - Catch any change to behavior (ensure refactoring changes are non-functional)
    - Ensure control algorithms achieve mission objectives
- Checkpoint/restore tests
- Exploratory tests
    - Logged data posted to reviews
- Software-in-the-loop
    - Medium-scale integration test
    - Leverage virtualization, preloading, hardware simulation
    - Subsystem and end-to-end scope
- Hardware-in-the-loop
    - Large-scale integration test
    - Verify non-functional requirements
- Vehicle-in-the-loop
    - Large-scale integration test
    - Verify a particular "production unit"
- Formal test deliverables

{% enddetails %}
{% details Flaky vs. brittle tests %}

- Flaky
    - Non-deterministic failures
        - Multi-process/multi-node
        infrastructure failures
        - Performance/timeouts
        - Randomness
        - Always log seed
        - Concurrency
        - Difficult to reproduce
        - Time of day
- Brittle
    - "High maintenance"
        - Leverage private functionality
        - Depend on private state
        - Assume behavior beyond the spec
            - e.g. checking interactions instead of state
    - Coming up: guidelines to avoid
    brittle tests

{% enddetails %}
{% details Aside: random numbers %}

- In most settings, random numbers should be deterministic
    - Enables reproducibility, reduces test flakiness
    - Exceptions (in production): cryptography, gambling
- Recommended approach
    - Application starts with a specified global seed (and logs it)
    - Each component constructs a private RNG by combining global seed with unique
    instance name
    - Alternative for parallel computation: sequence queries, use RNG that can "fast
    forward" state
- Advantages
    - Results independent of amount of parallelism
    - Results do not change if "peripheral" components are added or removed

{% enddetails %}
{% details Test scope %}

- Small scope
    - Limited coverage (per test)
    - But coverage is orthogonal
    - May require awkward setup (dependency
    injection, mock objects)
    - Can be written simultaneously with the code-under-test
    - Easy to diagnose
        - Limited amount of code is executed
        - Easier to understand procedure and results
    - Typically faster
        - Can run more often
- Large scope
    - Extensive coverage (per test)
        - Much coverage is redundant
        - Most results are not checked (false sense of security)
    - May be easier to set up than mid-scoped tests
        - But total configuration harder to reason about
    - Depends on whole system
        - Bugs may not be found until later
    - Difficult to diagnose
        - Slows down debugging when bugs are found
    - Typically slower

{% enddetails %}
{% details Exploratory testing %}

- Applications
    - Developers check how existing code
    behaves
    - Developers "gut check" new code
    - Demonstrate functionality in a scenario of interest with complicated setup
    - QA testing (test behaviors developers often overlook)
- Tools
    - Application itself (print)
    - REPL (JShell, iPython)
    - Dynamic analysis tools (callgrind)
- Drawbacks
    - Not reproducible
        - Results may depend on unique context
        - Good habit to log all interactions
    - Good to think about expectations before running test, but if you can
    express what you expect, just write a unit test
    - Quality varies with tester
        - Can't measure coverage
- Appropriate for one-off scripts

{% enddetails %}
{% details Unit tests %}

- Narrow scope (typically a single function or a single class)
- Focus on publicly-visible, fully-specified behavior
    - Check state, not process
- Write for clarity
    - Okay to be repetitive
    - Avoid new abstractions or logic
- Bad example:
    - When registering a new user, the system first generates a password,
    then tries to insert a new auth table row, throwing an exception if insertion failed (name already taken)
- Better example:
    - After registering a new user whose name is not taken, a new row will
    exist in the database with their username and password
    - If attempting to register a new user whose name is already taken, an
    exception is thrown.

{% enddetails %}
{% details Behavior-driven development %}

- Structuring tests around methods can make them brittle, hard to read
    - Try to test too many behaviors at once
- Better to structure tests around scenarios
- Arrange-act-assert format
    - "Given ..., when ..., then ..."
    - Analogous to User Stories preamble
- `Given` two accounts, the first of which has at least $100, `when` transferring $100 from 
the first to the second account, `then` both account balances should reflect the transfer"
- Test frameworks can help make tests self-documenting
- Consider writing tests `before` implementing features

{% enddetails %}
{% details Integration tests %}

- Broader scope
    - Check that multiple components interface correctly
    - Check behavior of subsystems
- Tend to be larger in size
    - SoA requires multiple processes
    - Non-trivial data, config can be slow
    - Aim for smallest test possible
        - Split pipelines into pairwise interactions
- Larger tests require non-trivial infrastructure, can be flaky
    - Fakes
    - Lightweight substitutions
        - In-memory databases
    - Hermetic services
        - Leverage virtualization to deploy isolated instances of service dependencies
    - Record/replay I/O
        - Trades flakiness for brittleness

{% enddetails %}
{% details Integration environments %}

- Production
    - Highest fidelity, esp. for load
    - Failures affect real users
    - Canarying: deploy to subset of production systems
    - E.g. internal users, early access
    - Can lead to version skew – incompatibility between concurrently-running components
    - Feature flags: Allow operators to quickly toggle between new and old implementation
- Staging
    - Ideally configured just like production
    - Potentially high infrastructure cost, limited availability
    - Often can't duplicate production load
    - Failures do not harm users
    - Can practice disaster recovery

{% enddetails %}
{% details Chaos engineering %}

- Originated at Netflix (ChaosMonkey)
- High-reliability, distributed systems must tolerate failure
- Recovery procedures are often not sufficiently rehearsed – painful, risky
- Deliberately inject failures in production environment
    - Tests system resiliency under realistic load
    - Encourages recovery automation

{% enddetails %}
{% details note Continuous integration ("CI") %}

- Build and test whole systems regularly
    - Discover issues earlier
    - Reduce integration pain through automation and isolation of issues
    - Test beyond single developer's resources
    - Eliminate reliance on developers' discipline
    - Continuously monitor readiness of code
- Applies to both development and release
    - Continuous build+test
    - Continuous delivery

{% enddetails %}
{% details CI decisions %}

- `How` to compose systems along release workflow
- `Which` tests to run `when` along release workflow
- Typical setup
    - Pre-submit test suite gates all merges
        - Compilation and fast tests relevant to affected code
    - Post-submit test suite verifies subset of commits on trunk
        - Contains larger, more integrated tests
        - Blesses commits that pass as "green"
    - Release promotion pipeline verifies candidates for release
        - Contains even larger tests, may require dedicated resources

{% enddetails %}
{% details Automation, speed, & infrastructure %}

- Builds, tests, and deployment must be automated and reliable
    - Ideally completely reproducible
- Most steps must be fast to avoid impeding productivity
    - Cache build products
    - Skip unaffected tests
    - Parallelize & invest in compute resources
- Benefits from tooling
    - Integration with version control and code review
        - Pre-merge and pre-release gates
        - "Last-known-good" branch (new work should branch from here, not trunk)
    - Bisect breakages
    - Log all results
    - Automatically rerun flaky tests

{% enddetails %}
{% details Multi-system CI %}

- Without monorepo, need to assemble system from several
asynchronously-versioned repositories
- Large integration tests can't check every revision/combination
- Objective: identify "configurations" (revision combinations) suitable
for promotion (larger-scale testing, release)


{% enddetails %}
## Dynamic analysis

{% details Common dynamic analysis tools %}

- Coverage
- Debuggers
- Memory checkers
- Sanitizers
- Profilers

{% enddetails %}
{% details Fuzz testing %}

- Give program random input, look for crashes, assertion violations
- Increased in popularity in 2010s; very effective at finding security
vulnerabilities
- Can be enhanced with coverage feedback
- Use genetic algorithms, neural networks to construct input that exercises
particular branches

{% enddetails %}
{% details What is a performance bug? %}

- Avoid premature optimization!
- Does not meet deadlines / satisfy SLA
- Responsiveness, smoothness do not meet requirements
    - 100 ms: GUI
    - 15-30 ms: Animation (30-60 fps)
    - 10 ms: MIDI, VR
- Unexpected slowdown for certain inputs / DoS vulnerability
- Performance regression (gradual and acute degradation)
- Performance variability across platforms
- Sub-optimal throughput for HPC

{% enddetails %}
{% details Performance testing challenges %}

- How much room for improvement is there?
    - Amdahl's law: Limits to speedup from parallelization, local optimization
    - Roofline analysis: Do you expect to be limited by bandwidth or compute?
- Is slowdown localized, dispersed, or emergent?
- Getting reliable measurements is difficult
    - Inconsistency, load dependency, JIT compilation, non-representative datasets,
    intrusive tooling
    - Average case vs. worst case, tail metrics
    - Tension between latency and bandwidth

{% enddetails %}
{% details Latency vs. throughput %}

- Latency: Duration between a single trigger and the system's response
    - "Tail latency" (e.g. 95th percentile under a specified load) is more important than average
- Throughput: Time it takes to processes a fixed amount of work
    - Often a function of workload
        - Typically throughput increases with workload size up to a saturation point
    - Reduce overhead with batching
        - Typically at expense of latency

{% enddetails %}
{% details Discussion %}

- Consider adding new elements to a sorted list (initial size N) while 
maintaining sorted order.
- Scenario A: Elements are inserted into their proper position one at a time.
- Scenario B: All elements are appended to the list, then the whole list is
sorted (comparison sort).
{% enddetails %}
