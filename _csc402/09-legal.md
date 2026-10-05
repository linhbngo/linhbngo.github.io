---
layout: lecture
pretty_table: true
order: 11
title: "Licensing and Legal Considerations"
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true

toc:
  - name: Logistics
  - name: Marketing
  - name: Legal context
  - name: Software licensing
  - name: Patents and trade secrets
  - name: Professionalism & Ethics
---


## Legal context

{% details Law %}

{% details danger Details %}

I am not a lawyer, (`IANAL`); this is not legal advice

{% enddetails %}

{% details warning Scope and currency %}

This lecture is primarily a US-oriented overview, checked against official
sources in October 2026. Privacy, employment, contract, and intellectual
property rules vary by jurisdiction and change over time. The linked primary
or agency sources are starting points, not substitutes for advice about a
specific situation.

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

- Do not rely on an AI tool as legal authority or as a substitute for qualified
  counsel. It can omit controlling law, invent citations, or apply the wrong
  jurisdiction. Verify primary sources and obtain legal review for decisions
  with real consequences.
- Law is not code: it cannot be parsed, reasoned about, or `debugged` by logic alone. The legal system is complex, 
inconsistent, and deeply human.

{% enddetails %}
{% enddetails %}

{% details Jurisdiction %}

- United States law comes from several sources:
    - federal and state constitutions;
    - statutes enacted by Congress and state legislatures;
    - regulations issued by agencies under delegated authority;
    - treaties and local law; and
    - judicial decisions, including precedent in common-law adjudication.
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

- [Computer Fraud and Abuse Act](https://www.justice.gov/jm/jm-9-48000-computer-fraud)
  (CFAA, 1986)
    - Criminalizes specified conduct involving access to protected computers
      "without authorization" or by "exceeding authorized access."
    - After *Van Buren v. United States* (2021), merely misusing information one
      was entitled to access is not automatically an
      "exceeds authorized access" offense. Authorization remains a
      fact- and jurisdiction-sensitive question.
- [Digital Millennium Copyright Act](https://copyright.gov/dmca/) (DMCA, 1998)
    - Section 1201 generally prohibits circumvention of technological access
      controls and trafficking in circumvention tools, subject to permanent
      and periodically renewed exemptions.
    - Separately, Section 512 limits copyright-infringement liability for
      qualifying online service providers that satisfy applicable safe-harbor
      conditions; it is not blanket immunity for users' actions.
- [General Data Protection Regulation](https://commission.europa.eu/law/law-topic/data-protection/legal-framework-eu-data-protection_en)
  (GDPR): entered into force in 2016 and has applied since May 25, 2018.
- [California Consumer Privacy Act](https://oag.ca.gov/privacy/ccpa) (CCPA):
  effective January 1, 2020, and substantially amended by the California
  Privacy Rights Act (CPRA), whose principal provisions took effect January 1,
  2023.
    - GDPR processing requires an applicable lawful basis. Consent and
      legitimate interests are only two of six Article 6 bases.
    - Online identifiers such as cookie IDs can be personal data. Whether a
      cookie requires consent also depends on the EU ePrivacy rules; strictly
      necessary cookies are treated differently from advertising or tracking
      cookies.

{% enddetails %}

{% details Other laws affecting software %}

- Contracts
- Copyright
- Patents
- Trade secrets
- Export
- Privacy

{% enddetails %}


## Software licensing

{% details Copyright %}

- Broad international consensus thanks to Berne Convention
- Applies to "expression of ideas"
    - Originally literary and artistic works
- Established automatically when an original work is fixed in a tangible medium; registration is not required for copyright to exist in the US, although registration provides important enforcement benefits
    - Initially held by the author except for a qualifying `work made for hire`
      or a valid transfer
- Can be transferred
- Rights can be licensed
- Holder has exclusive right to:
    - Reproduce
    - Prepare derivative works
    - Distribute
    - Publicly perform or display categories of protected works
    - License rights to others
- Exceptions
    - First sale: the owner of a lawfully made copy can generally dispose of
      that particular copy; this does not transfer copyright and has
      software-specific limitations
    - Fair use: a context-specific, four-factor defense, not automatic
      permission. Criticism, comment, news reporting, teaching, scholarship,
      and research are illustrative purposes, not guaranteed safe categories.

See the
[U.S. Copyright Office overview](https://copyright.gov/what-is-copyright/).

{% enddetails %}

{% details Joint authorship %}

- A joint work requires two or more authors to intend that their
  copyrightable contributions be merged into inseparable or interdependent
  parts of one work. Working in the same repository does not by itself settle
  joint authorship.
- A joint owner can generally grant a nonexclusive license without the other
  owners' permission, but must account to co-owners for their share of
  licensing revenue. Exclusive licenses ordinarily require all owners.
- Ownership shares are generally equal absent an agreement, even when the
  contributions differ, but project agreements and jurisdiction matter.
- CSC 402 projects may be joint works, collective works, or separately owned
  contributions depending on intent and the facts. Use a written project
  agreement rather than assuming.
- FERPA is separate from copyright. It restricts an educational institution's
  disclosure of education records; it does not determine copyright ownership
  or generally prevent a student from publishing their own work. Identifiable
  work maintained by the institution may still be an education record.

{% enddetails %}
{% details Work for hire %}

- In US copyright law, work created by an employee within the scope of
  employment is generally a **work made for hire**, making the employer the
  initial author and owner. Employment agreements also commonly assign patent
  rights and rights in work outside that rule.
    - You may need the employer's permission before contributing to an
      open-source project, especially when the contribution relates to your
      work, uses employer resources, or falls within an invention-assignment
      agreement. Check the agreement and company policy.
    - Can be negotiated at time of employment
    - Can ask for a copyright disclaimer to protect against future claims
- A freelancer ordinarily owns copyright initially. A commissioned work is a
  work made for hire only if it falls within a statutory category and the
  parties sign an express written agreement. Otherwise, ownership can be
  transferred only through a signed writing; a contract should clearly state
  ownership and license rights.
- If you do not hold the copyright, you need explicit permission to copy
or use software, even if you wrote it yourself (retaining a backup for
personal use is not automatically allowed)

{% enddetails %}
{% details Contract and copyright law %}

- Commercial software transactions often combine copyright and contract law.
    - Many products license software rather than transferring ownership, but
      the legal characterization depends on the transaction and jurisdiction.
    - End User License Agreements (EULAs), including clickwrap agreements, are
      contracts when enforceable; they are not an alternative to contract law.
      Enforceability depends on adequate notice and assent.
- Contracts also govern software
development work
    - Who will own copyright
    - Exclusivity of licensing
    - Contingency terms
- Most open-source licenses
leverage copyright law

{% enddetails %}
{% details Open-source software licenses %}

- "Free as in beer" means **gratis**, but zero price is not a requirement of
  open source. The
  [Open Source Definition](https://opensource.org/osd) permits selling
  open-source software and prohibits the license from restricting resale.
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


{% include figure.liquid path="assets/img/courses/csc402/copyright.png" max-width="50%" zoomable=true %}    

{% enddetails %}
{% details Copyleft %}

- Copyleft obligations depend on the specific license, what constitutes the
  covered work, and whether a triggering event such as conveying/distributing
  it occurs. Strong copyleft licenses commonly require recipients to receive
  corresponding source and the applicable license rights.
    - Ordinary internal use does not trigger the GPL's source-distribution
      obligations, although transfer to another legal entity can. The AGPL has
      an additional network-interaction provision.
- Epitomized by the GNU General Public License (GPL)
    - The Free Software Foundation takes the position that static or dynamic
      linking generally creates one combined program. Whether a particular
      boundary creates a derivative work is fact-specific and not conclusively
      resolved for every architecture.
- Other examples:
    - Mozilla Public License (file-level copyleft)
    - Creative Commons ShareAlike licenses are copyleft-like licenses for
      creative works, but
      [Creative Commons recommends against using CC licenses for software](https://creativecommons.org/faq/#can-i-apply-a-creative-commons-license-to-software).

{% enddetails %}
{% details GPL variations %}

- Lesser GPL (LGPL)
    - Applications linking to an LGPL
    library do not have to be
    distributed under the same license, but distribution still carries
    LGPL-specific notice, source, and relinking or reverse-engineering
    obligations
    - Wording is C-centric
- GPL with classpath exception
    - Permits specified independent modules to link to the covered library
      without subjecting the entire resulting executable to the GPL
    - Intended for runtime support and
    standard libraries
- Affero GPL (AGPL)
    - If a modified AGPL-covered program supports remote network interaction,
      Section 13 requires offering those remote users its Corresponding Source.
      It does not require publishing every component on the server merely
      because the components run on the same machine.

{% enddetails %}
{% details Other constraints %}

- Advertising clause
    - In original BSD license; not
    scalable
- Patent rights
    - Some modern licenses expressly grant recipients rights under patent
      claims controlled by contributors; the scope and conditions vary by
      license. Do not assume that a copyright license grants every patent right
      needed to use the software.
- Some licenses, including Apache-2.0 and GPLv3, contain patent-retaliation or
  termination provisions triggered by specified patent claims; this is not a
  universal feature of every open-source license.
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
    - Contributions accepted by an open-source project are commonly licensed
      under that project's license. GitHub's Terms of Service expressly use
      this default unless a separate agreement applies.
    - Copyright is held by contributors
- Contributor License Agreements
    - Assert contributors' right and intent to contribute
    - Potentially assign copyright to project stewardship
    - Potentially grant project steward right to relicense/dual license
    - Some projects require a CLA before accepting a contribution; many do
      not. Follow the project's contribution policy.
- Developer Certificate of Origin
    - Lightweight agreement acknowledged in commit message ("Signed-Off-By:")

{% enddetails %}
{% details Applying a license %}

- Add a LICENSE file to the root of your repository
- Add a copyright and license notice header to every file
    - Not always required; see license documentation for recommendation
- Track licenses of dependencies and contributions with SPDX identifiers
    - Facilitates license compliance and assembling a software bill of
      materials (SBOM). An SBOM is primarily an inventory of components and
      relationships; it can include license and copyright metadata.
    - When creating a software product, you must have documented rights to use
    everything from which it was derived

{% enddetails %}
{% details Licensing CSC 402 projects %}

- External projects relinquish all IPs to the clients
- Internal projects must agree on how contributions should be licensed
    - Option 1: Agree to publish under inbound=outbound (can share on public GitHub,
    include in portfolio, contribute upstream)
    - Option 2: Treat as private coursework. The institution should not publish
      identifiable student work without consent or another applicable FERPA
      exception; students can consent to publication or publish work they have
      the rights to publish.

{% enddetails %}
{% details Resources %}

- https://opensource.guide/legal/
- https://choosealicense.com/appendix/
- https://www.gnu.org/licenses/license-list.html (biased, but thorough)

{% enddetails %}

## Patents and trade secrets

{% details Patents %}

- Grants an inventor or assignee a time-limited right over the invention
  defined by the patent's claims. Patents do not protect abstract ideas as
  such; eligible subject matter and adequate disclosure are also required.
- A US utility-patent claim generally must be useful, novel, and non-obvious
- Patent rights
    - Exclude others from
    making, using, offering to sell, selling, or
    importing the invention
- Must submit an application to
be granted a patent
    - Public disclosure in exchange
    for exclusive rights
    - US utility and plant patents generally can last up to 20 years from the
      earliest qualifying nonprovisional filing date, subject to maintenance
      fees and possible adjustments or extensions. US design patents filed on
      or after May 13, 2015 generally last 15 years from grant.
- Once granted, patent validity can
be challenged in court
    - Extremely expensive; high burden
    of proof
    - Most patent disagreements are
    settled out of court

See the USPTO's
[Patent essentials](https://www.uspto.gov/patents/basics/essentials).

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
    - "Patent troll" is a pejorative term commonly used for a
      non-practicing entity whose business model emphasizes acquiring patents
      and asserting them for settlements or licensing revenue
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
    - Historically encumbered by patents, including IBM patents that expired
      by approximately 2010
    - Support remains much less common than Huffman-coded baseline JPEG, so it
      is rarely used for interoperable web images
- H.264/AVC (MPEG-4 Part 10)
    - [Via Licensing Alliance](https://www.via-la.com/licensing-programs/avc-h-264/)
      now administers the AVC/H.264 pool formerly administered under the
      MPEG LA name. 
    - Patents cover not just encoding and decoding, but also transmission
    - Cisco's OpenH264 arrangement covers pool royalties for Cisco-distributed
      binaries only under the
      [binary license's conditions](https://www.openh264.org/BINARY_LICENSE.txt).
      Building or distributing the BSD-licensed source yourself does not
      receive Cisco's patent coverage, and pool coverage does not guarantee
      rights under every possible third-party patent.

{% enddetails %}
{% details Trade secrets %}

- Companies can protect confidential business information
- Owner must make reasonable effort to maintain secrecy
- Employees may not disclose trade secrets, competitors may not use secrets obtained via improper means
    - A limited disclosure under a duty of confidentiality may preserve
      secrecy, but public disclosure can destroy trade-secret status.
    - Protection can continue indefinitely only while all required elements,
      including secrecy and reasonable protective efforts, continue to exist.
- Non-disclosure agreements (NDAs)
    - Legal agreement to not disclose trade
    secrets
    - Common precondition for
    employment or even interviewing
    - But still read carefully

See the
[USPTO trade-secret overview](https://www.uspto.gov/ip-policy/trade-secret-policy).

{% enddetails %}
{% details Export law %}

- Governments restrict what can be exported, even "intellectual property"
- Common export regulations affecting US software:
    - International Traffic in Arms Regulations (ITAR)
    - Export Administration Regulations (EAR)
- Intent: prevent export of goods and information that could assist
adversaries in harming national interests
    - Applies to many aerospace technologies
    - Cryptography remains subject to US export controls. Many products can be
      exported under License Exception ENC after applicable classification,
      notification, and reporting, while destination, end-user, and end-use
      restrictions still apply. See the
      [Bureau of Industry and Security encryption guidance](https://media.bis.gov/learn-support/encryption-controls).
    - Historical "export-grade" cryptography weakened deployed protocols and
      later enabled attacks; today's rules are less restrictive but have not
      disappeared.
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
    - Gives parents and eligible students rights concerning education records
      maintained by covered educational institutions and generally limits
      institutional disclosure without consent, subject to exceptions
    - Grades should be private to individuals
    - Enrollment status may be designated as directory information after
      required notice and an opportunity to opt out; identifiable student work
      may be an education record. 
- HIPAA
    - Applies to covered health plans, health care clearinghouses, certain
      health care providers, and their business associates—not to every app or
      company that handles health-related data.
    - A vendor that creates, receives, maintains, or transmits protected health
      information for a covered entity generally needs an appropriate business
      associate agreement (BAA). Buying a vendor's higher service tier alone
      does not make the customer's system compliant.

See the official
[FERPA guidance](https://studentprivacy.ed.gov/ferpa) and
[HIPAA covered-entity guidance](https://www.hhs.gov/hipaa/for-professionals/covered-entities/index.html).

{% enddetails %}


## Professionalism & Ethics
    
{% details Responsible disclosure %}

- AKA "coordinated vulnerability disclosure"
- Coordinate timing of announcement with vendor
    - Give them time to patch products, prepare press response
    - Establish a disclosure deadline appropriate to severity and policy.
      Ninety days is one well-known policy, and actively exploited vulnerabilities may justify much shorter timing.
- For open-source projects, look for security policy (SECURITY.md)
    - Contact Vulnerability Management Team or owner
    - Do not post details to public mailing lists, chat rooms
- A CVE Record may remain `RESERVED` while remediation and disclosure are
  coordinated; the identifier alone does not disclose technical details

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

{% details Joint ACM/IEEE-CS Software Engineering Code of Ethics %}

The following are the eight short principles from version 5.2 of the
[Software Engineering Code of Ethics and Professional Practice](https://www.acm.org/code-of-ethics/software-engineering-code),
jointly approved by ACM and IEEE-CS. This is distinct from the broader ACM
Code of Ethics and Professional Conduct.

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
