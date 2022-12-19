

/****** Object:  Table [dbo].[Policies]    Script Date: 27/08/2022 9:34:16 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Policies](
	[PQID] [int] IDENTITY(1,1) NOT NULL,
	[CompNo] [nvarchar](50) NOT NULL,
	[BranchNo] [nvarchar](50) NOT NULL,
	[IntermediaryNo] [nvarchar](50) NOT NULL,
	[ClientNo] [nvarchar](50) NOT NULL,
	[LifeAssured] [nvarchar](50) NOT NULL,
	[DOB] [date] NOT NULL,
	[PolicyNo] [nvarchar](100) NOT NULL,
	[QuoteNo] [nvarchar](50) NULL,
	[QuoteDate] [date] NOT NULL,
	[ProductNo] [nvarchar](50) NOT NULL,
	[CommenceDate] [date] NOT NULL,
	[PolicyTerm] [float] NOT NULL,
	[LastPremiumDate] [date] NOT NULL,
	[MaturityDate] [date] NOT NULL,
	[PaymentFrequency] [nvarchar](50) NOT NULL,
	[PayoutFrequency] [nvarchar](50) NULL,
	[AssumedInterestRate] [float] NOT NULL,
	[SumAssured] [money] NOT NULL,
	[PremiumAmount] [money] NOT NULL,
	[TotalPremiumPayable] [money] NOT NULL,
	[PolicyStatus] [nvarchar](50) NOT NULL,
	[CreatedBy] [nvarchar](50) NOT NULL,
	[CreatedDate] [datetime] NOT NULL,
	[UpdatedBy] [nvarchar](50) NOT NULL,
	[UpdatedDate] [datetime] NOT NULL,
	[WorkStation] [nvarchar](100) NOT NULL,
	[AssuredIDNo] [nvarchar](100) NULL,
	[AssuredRelshp] [nvarchar](100) NULL,
	[CurrentAKISNo] [nvarchar](100) NULL,
	[AlternateRefNo] [nvarchar](100) NULL,
 CONSTRAINT [PK_Policies] PRIMARY KEY CLUSTERED 
(
	[PolicyNo] ASC,
	[ProductNo] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[Policies]  WITH CHECK ADD  CONSTRAINT [FK_Policies_BranchMaster] FOREIGN KEY([BranchNo])
REFERENCES [dbo].[BranchMaster] ([BranchNo])
GO

ALTER TABLE [dbo].[Policies] CHECK CONSTRAINT [FK_Policies_BranchMaster]
GO

ALTER TABLE [dbo].[Policies]  WITH CHECK ADD  CONSTRAINT [FK_Policies_Clients] FOREIGN KEY([ClientNo])
REFERENCES [dbo].[Clients] ([ClientNo])
GO

ALTER TABLE [dbo].[Policies] CHECK CONSTRAINT [FK_Policies_Clients]
GO

ALTER TABLE [dbo].[Policies]  WITH NOCHECK ADD  CONSTRAINT [FK_Policies_CompanyMaster] FOREIGN KEY([CompNo])
REFERENCES [dbo].[CompanyMaster] ([CompNo])
GO

ALTER TABLE [dbo].[Policies] CHECK CONSTRAINT [FK_Policies_CompanyMaster]
GO

ALTER TABLE [dbo].[Policies]  WITH CHECK ADD  CONSTRAINT [FK_Policies_Intermediaries] FOREIGN KEY([IntermediaryNo])
REFERENCES [dbo].[Intermediaries] ([IntermediaryNo])
GO

ALTER TABLE [dbo].[Policies] CHECK CONSTRAINT [FK_Policies_Intermediaries]
GO

ALTER TABLE [dbo].[Policies]  WITH CHECK ADD  CONSTRAINT [FK_Policies_PolicyProductsDetails] FOREIGN KEY([ProductNo])
REFERENCES [dbo].[PolicyProductsDetails] ([ProductNo])
GO

ALTER TABLE [dbo].[Policies] CHECK CONSTRAINT [FK_Policies_PolicyProductsDetails]
GO


