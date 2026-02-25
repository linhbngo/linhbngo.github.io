---
layout: lecture
pretty_table: true
collection: csc402
course: CSC 402: Software Engineering.
title: "Licensing and Legal Considerations"
toc:
  - name: Logistics
  - name: Marketing
  - name: Legal context
  - name: Software licensing
  - name: Patents and trade secrets
  - name: Professionalism & Ethics
  - name: Examples
---
# Licensing and Legal Considerations

---

## Logistics

- Last day of the course: Thursday December 4th 
- Final presentation periods:
    - November 20 (2 presentation spots) - Do you want to do November 25?
    - December 4th (2 presentation spots)
    - December 2nd (2 presentation spots)
    - Attendance: Mandatory for ALL member, whether your team presents or not. 
- Capstone Showcase
    - Friday December 5th, 9:30AM - 12:00PM
    - Sikes Theater

---

## Marketing

Write a short paragraph describes the project that your team is working on. Feel free to name-drop/mention the client company, 
or explicitly mention `legacy project` aspects of your project. I will be using these paragraphs to send an invite to the Dean, 
other students in the depatrment, the Career Development Center (and asks them to invite vendors). 

___

## Legal context

{% details Law %}

{% details danger Details %}

I am not a lawyer, (`IANAL`); this is not legal advice

{% enddetails %}
- Law is not code or pure logic
    - Definitions are ambiguous
    - Implications may be inconsistent
    - Consequences are not automatic
    - Interpreted by humans
- Law is not uniform
    - Varies by jurisdiction
    - Changes over time
    - Interpretation varies by judge
- Law is serious
    - Penalties include millions to billions of dollars in fines,
    destruction of inventory, jail time
    - Court cases are slow and expensive
- Do not try to interpret the law on
your own
    - Might be reading the wrong law
    - May not be aware of case precedent
    - People on the Internet can be wrong
    (gasp!)
- Most companies retain legal
counsel – take advantage of them

{% details danger Details %}

- Do not use AI tools to interpret or apply the law.
- Law is not code: it cannot be parsed, reasoned about, or `debugged` by logic alone. The legal system is complex, 
inconsistent, and deeply human.

{% enddetails %}
{% enddetails %}
{% details Jurisdiction %}

- The United States follows Common Law, composed of:
    - Statues (bills) passed by Congress
    and states
    - Regulations issued by government
    - Precedents (judgements) made by
    courts
- Federal law and state laws, each with their own multi-layered
court systems
- International law is complex and
dynamic, especially regarding Internet services
    - A user, the server that they access,
    the server where their data is
    stored, and the headquarters of
    the company running the service
    may all be in different
    countries. Each country may claim
    jurisdiction over the service.

{% enddetails %}
{% details Computing-specific laws %}

- Computer Fraud and Abuse Act (1986)
    - Explicitly prohibits unauthorized access of computing systems
- Digital Millenium Copyright Act (DMCA, 1998)
    - Prohibits circumvention of access control to copyrighted works
- Limits liability of service providers for actions by their users
- General Data Protection Regulation (GDPR, 2016), 
- California Consumer Privacy Act
(2020)
    - Restricts use of personal data – requires consent or legitimate interest
    - Browser cookies qualify as personal data

{% enddetails %}
{% details Other laws affecting software %}

- Contracts
- Copyright
- Patents
- Trade secrets
- Export
- Privacy

{% enddetails %}
---

## Software licensing

{% details Copyright %}

- Broad international consensus thanks to Berne Convention
- Applies to "expression of ideas"
    - Originally literary and artistic works
- Established automatically when work is created
    - Initially held by creator except for `work for hire`
- Can be transferred
- Rights can be licensed
- Holder has exclusive right to:
    - Reproduce
    - Use as basis for derived works
    - Distribute
    - Exhibit in public
    - License rights to others
- Exceptions
    - First sale: objects containing
    copyrighted work can be resold
    - Fair use: limited use is allowed
    without permission for special
    purposes (review, quotation)

{% enddetails %}
{% details Joint authorship %}

- Each coauthor can independently exercise their copyright rights
(including licensing to third parties) without permission of other
coauthors
- But by default, coauthors must share all profits equally with one
another
- CSC 402 project contributions probably qualify as joint authorship
    - But is also protected by FERPA

{% enddetails %}
{% details Work for hire %}

- When working for an employer, you often assign all patent and
copyright rights to them
    - Will need employer's permission before contributing to open-source projects
    - Can be negotiated at time of employment
    - Can ask for a copyright disclaimer to protect against future claims
- If doing freelance work, must have a contract with the client that
declares ownership of copyright
- If you do not hold the copyright, you need explicit permission to copy
or use software, even if you wrote it yourself (retaining a backup for
personal use is not automatically allowed)

{% enddetails %}
{% details Contract and copyright law %}

- Most commercial software
licenses fall under contract law
    - Software is not purchased for
    ownership; it is licensed for use
    - End User License Agreements
    (EULAs) are an alternative to
    signed contracts
- Contracts also govern software
development work
    - Who will own copyright
    - Exclusivity of licensing
    - Contingency terms
- Most open-source licenses
leverage copyright law

{% enddetails %}
{% details Open-source software licenses %}

- "Free as in beer" (gratis)
    - Users do not need to pay money
    to use the program
- "Free as in speech" (libre)
    - Users of software should be
    guaranteed freedoms, such as:
    - Free to use the software for any
    purpose
    - Free to read and modify source code
    - Free to distribute copies
- Two underlying philosophies:
    1. An open development model
    leads to better software ("open
    source" movement)
    2. Software should not violate
    users' freedoms (Free Software
    Foundation)

{% enddetails %}
{% details Permissive and copyleft licenses %}


{% include figure.liquid path="assets/img/courses/csc402/copyright.png" width="50%" zoomable=true %}    

{% enddetails %}
{% details Copyleft %}

- If copyleft-licensed software is modified and redistributed, then
the redistributed software must be under the same (or a compatible) license
    - In particular, source code must be
    made available
    - Not a concern for internal use – if
    software is not released to the
    public, source code may remain
    private
- Epitomized by the GNU General
Public License (GPL)
    - The GPL considers linking (both
    static and dynamic) to constitute a
    "derived work"
- Other examples:
    - Mozilla Public License 
    - Creative Commons Share-Alike

{% enddetails %}
{% details GPL variations %}

- Lesser GPL (LGPL)
    - Applications linking to an LGPL
    library do not have to be
    distributed under the same license
    - Wording is C-centric
- GPL with classpath exception
    - Also removes virality, but more
    language-agnostic
    - Intended for runtime support and
    standard libraries
- Affero GPL (AGPL)
    - Providing network services linked
    with AGPL software requires
    making the server's source code
    available

{% enddetails %}
{% details Other constraints %}

- Advertising clause
    - In original BSD license; not
    scalable
- Patent rights
    - Recipients of the software are
    granted rights to applicable
    patents as required for running
    the software
- Patent rights revoked if you
claim patent infringement
- Trademarks and non-
endorsement
    - May not be necessary to state
    explicitly
- Limited liability & lack of
warranty
- Attribution
    - Preservation of license and
    copyright notices

{% enddetails %}
{% details Licensing contributions %}

- "Inbound=outbound"
    - Contributions to an open-source project are implicitly licensed under that
    project's LICENSE at the time of commit (explicit on GitHub)
    - Copyright is held by contributors
- Contributor License Agreements
    - Assert contributors' right and intent to contribute
    - Potentially assign copyright to project stewardship
    - Potentially grant project steward right to relicense/dual license
    - Must be signed before any contribution can be accepted
- Developer Certificate of Origin
    - Lightweight agreement acknowledged in commit message ("Signed-Off-By:")

{% enddetails %}
{% details Applying a license %}

- Add a LICENSE file to the root of your repository
- Add a copyright and license notice header to every file
    - Not always required; see license documentation for recommendation
- Track licenses of dependencies, contributions with SPDX identifiers
    - Facilitates assembling a "software bill of materials" (licenses and copyrights of
    all included components)
    - When creating a software product, you must have documented rights to use
    everything from which it was derived

{% enddetails %}
{% details Licensing CSC 402 projects %}

- External projects should have signed a license agreement with their client
during session 1 or 2
    - Must at least grant comprehensive usage license (including permission to create and
    use derived works) to client
    - May transfer copyright to client
    - Agreement must be in writing and signed by all contributors
- Internal projects must agree on how contributions should be licensed
    - Option 1: Agree to publish under inbound=outbound (can share on public GitHub,
    include in portfolio, contribute upstream)
    - Option 2: Treat as coursework. Cannot publish if students are identifiable

{% enddetails %}
{% details Resources %}

- https://opensource.guide/legal/
- https://choosealicense.com/appendix/
- https://www.gnu.org/licenses/license-list.html (biased, but thorough)

{% enddetails %}
---

## Patents and trade secrets

{% details Patents %}

- Defines rights of inventors
    - Applies to ideas (whereas Copyright applies to an expression of ideas)
- Should be non-obvious, novel, and useful
- Patent rights
    - Exclude others from
    making, using, selling, or
    importing the invention
- Must submit an application to
be granted a patent
    - Public disclosure in exchange
    for exclusive rights
    - Patents last 20 years from filing
    date
- Once granted, patent validity can
be challenged in court
    - Extremely expensive; high burden
    of proof
    - Most patent disagreements are
    settled out of court

{% enddetails %}
{% details Software patents %}

- Problems
    - Collaborative and rapidly-advancing
    culture – difficult to know where
    ideas originate
    - Poor standards for examination leads
    to granting of broad patents for
    routine concepts
        - Some companies require filing patents
        for promotion
    - Broad patents may overlap –
    hundreds may cover the same idea
    - International differences
- Patent abuse
    - Large companies hoard patents
        - Can harass smaller competitors
        - Used as defense against other large
        companies
    - Patent trolls – business model is to
    collect unenforced patents and
    threaten litigation
        - Often harass smaller companies and
        end users
        - Large companies may pursue
        invalidation in court 
- If you receive letters threatening
litigation, consult a lawyer

{% enddetails %}
{% details Software patent examples %}

- Arithmetic coding
    - Alternative to Huffman coding in
    JPEG format
    - Reduces file size by up to 25%
    - Covered by IBM patents until 2010
    - Very few JPEG libraries support
    arithmetic coding; not used on
    Internet
- H.264 (MPEG-4 AVC)
    - MPEG LA maintains patent pool
    for most (but not all) required
    patents – over 6000
    - Patents cover not just encoding
    and decoding, but also
    transmission
    - Cisco provides a free binary codec
    for which they pay licensing fees
        - But rebuilding it from source would
        require you to pay your own fees

{% enddetails %}
{% details Trade secrets %}

- Companies can protect confidential
business information
- Owner must make reasonable
effort to maintain secrecy
- Employees may not disclose trade
secrets, competitors may not use
secrets obtained via extraordinary
means
    - Leaks do not invalidate trade secrets
    - Protections never expire
- Non-disclosure agreements (NDAs)
    - Legal agreement to not disclose trade
    secrets
    - Common precondition for
    employment or even interviewing
    - But still read carefully

{% enddetails %}
{% details Export law %}

- Governments restrict what can be exported, even "intellectual property"
- Common export regulations affecting US software:
    - International Traffic in Arms Regulations (ITAR)
    - Export Administration Regulations (EAR)
- Intent: prevent export of goods and information that could assist
adversaries in harming national interests
    - Applies to many aerospace technologies
    - Formerly applied to cryptography
        - Unintended consequence: compatibility with "export grade" cryptography makes services
        very insecure
- Penalties are harsh and apply to employees as well as companies

{% enddetails %}
{% details Privacy %}

- Computer systems often handle information that people would
consider private
- Questions
    - What information can you collect? (legally and ethically)
    - How should you store private information?
    - Where can you store private information?
    - Who can you disclose private information to?
    - When should/must private information be destroyed?
- Laws and social norms are changing rapidly

{% enddetails %}
{% details Common privacy regulations %}

- FERPA
    - Protects educational records of students
    - Grades should be private to individuals
    - Enrollment, work should be private to classroom
- HIPPA
    - Protects medical information
    - Often need special tiers of third-party services (e.g. AWS, Zoom) to be
    compliant

{% enddetails %}
---

## Professionalism & Ethics
    
{% details Responsible disclosure %}

- AKA "coordinated vulnerability disclosure"
- Coordinate timing of announcement with vendor
    - Give them time to patch products, prepare press response
    - Upper bound on timing to hasten vendor action (typ. 90 days)
- For open-source projects, look for security policy (SECURITY.md)
    - Contact Vulnerability Management Team or owner
    - Do not post details to public mailing lists, chat rooms
- May be assigned placeholder CVE to coordinate efforts without
disclosing details

{% enddetails %}
{% details Which of these development efforts would you be comfortable contributing to? %}

- Drug marketing campaign
- Click fraud
- Selling 0-days
- Reverse engineering
- Weaponized AI
- Selling personal data
- Bitcoin mining

{% enddetails %}
{% details Ethics %}

- Software can harm society beyond physical injury
- Personal fulfilment is important too
    - Take responsibility for your work
    - Avoid future regrets
- Compared to traditional engineering, software has less oversight and
wider impact
    - Amplification: One day's work can affect millions of people, consume millions of hours

{% enddetails %}
{% details Diversity %}

- Wider impact => more diverse user base
    - => More potential to reinforce stereotypes, inequity
- Failure to anticipate/respond to biased systems can lead to major
societal (not to mention reputational) harm
- Need to expand diversity during development (shift left)
    - More diverse developer teams
    - More diverse user testing
- "Single source of truth" does not apply to human society
    - Disputed borders
    - Different interpretations of words/phrases/symbols
    - Different value systems

{% enddetails %}
{% details Ethics extends beyond code %}

- Hiring practices
    - Beware affinity bias, groupthink
- Promotions/opportunities
    - Beyond mentoring - advocate for coworkers who do good work but seem to
    go unnoticed
- Decision-making
    - Don’t defend decisions solely on precedent
    - Look beyond direct “bottom line” impact

{% enddetails %}
{% details ACM Code of ethics and professional practice %}

1. PUBLIC – Software engineers shall act consistently with the public interest.
2. CLIENT AND EMPLOYER – Software engineers shall act in a manner that is in the best interests
of their client and employer consistent with the public interest.
3. PRODUCT – Software engineers shall ensure that their products and related modifications
meet the highest professional standards possible.
4. JUDGMENT – Software engineers shall maintain integrity and independence in their
professional judgment.
5. MANAGEMENT – Software engineering managers and leaders shall subscribe to and promote
an ethical approach to the management of software development and maintenance.
6. PROFESSION – Software engineers shall advance the integrity and reputation of the profession
consistent with the public interest.
7. COLLEAGUES – Software engineers shall be fair to and supportive of their colleagues.
8. SELF – Software engineers shall participate in lifelong learning regarding the practice of their
profession and shall promote an ethical approach to the practice of the profession.

{% enddetails %}
---

## Examples

{% details Causes of poor outcomes %}

- Normalization of risk
    - Space Shuttle Columbia
- Over-constrained compute resources
    - Numerous space systems
- Over-trust in inherited components
    - Ariane 5
- Discounting cost of “inert” or “extra” components
- Changing circumstances
- Poor client-dev understanding

{% enddetails %}
{% details Ask for help %}

- University team given government funds to build high-performance
gateway
- Promising young developer hired, assigned task
- Task too difficult, but he hid his problems for months
- Project cancelled, nothing delivered
    - Don’t try to maintain a reputation at expense of project
    - Asking for help is expected, helps team grow
    - Leaders must monitor new employees more closely

{% enddetails %}
{% details Know when to cancel %}

- Senior management (without consulting technical staff) decides to
replace administrative software with COTS solution
    - Adopted schedule and budget from vendor’s marketing (hopelessly
    optimistic)
- Staff became dispirited; many left, including CIO
- What should new CIO do?
    - Analyze situation, provide visibility to leadership
    - Identify work worth continuing
    - Cancel remainder of project

{% enddetails %}
{% details Know when to start over %}

- University working on a joint project with a company to develop new
system software
- After two years, junior developer convinced university leader that
technical approach was wrong
- University decided to start over, company decided to keep going
- Both finished around same time, university version was superior
- The best time to refactor is before the system is first deployed

{% enddetails %}
{% details Conclusions %}

- Software engineering is bigger than programming"
    - More stakeholders
    - Collaborative development
    - Quality has a cost
- Successful projects involve tradeoffs, communication
    - Different projects warrant different approaches
    - Big projects are possible
- With planning & teamwork, can accomplish far more than solo
{% enddetails %}
