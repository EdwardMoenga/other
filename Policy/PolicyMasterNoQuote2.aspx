<%@ Page Language="C#" AutoEventWireup="true" CodeFile="PolicyMasterNoQuote2.aspx.cs" Inherits="Investment_PolicyMasterNoQuote2" %>

<%@ Register Assembly="DevExpress.Web.v15.1, Version=15.1.5.0, Culture=neutral, PublicKeyToken=b88d1754d700e49a" Namespace="DevExpress.Web" TagPrefix="dx" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1 {
            width: 100%;
        }

        .topPanel {
            padding-left: 0 !important;
            padding-right: 0 !important;
        }

            .topPanel .btn {
                margin-right: 12px;
            }

        body, form {
            padding: 0;
            margin: 0;
        }

        .nav {
            margin: 0;
            padding: 0;
            display: inline;
            width: 100%;
            padding-left: 15px;
        }

        .dxflItemSys {
            text-align: left;
        }

        .dxflVATSys {
            vertical-align: top;
        }

        .dxflCaptionCellSys { /* Bootstrap correction */
            -webkit-box-sizing: content-box;
            -moz-box-sizing: content-box;
            box-sizing: content-box;
        }

        .dxflHALSys {
            text-align: left;
        }
    </style>
</head>
<body>

    <form id="form1" runat="server">
        <dx:ASPxPanel ID="TopPanel" runat="server" FixedPosition="WindowTop" ClientInstanceName="topPanel" CssClass="topPanel" Theme="Aqua">
            <PanelCollection>
                <dx:PanelContent runat="server" SupportsDisabledAttribute="True">
                    <div class="titleContainer">
                        <dx:ASPxMenu ID="mMain" runat="server" EnableAdaptivity="true" Width="100%" HorizontalAlign="Center" Theme="Aqua">
                            <ClientSideEvents ItemClick="function(s, e) {
switch(e.item.name)
{
case &quot;mnuAdd&quot;:
if(ASPxClientEdit.ValidateGroup('Policies')==true){
cpAdd.PerformCallback('Add');
}
else{
return false;
}
break;
case &quot;mnuDelete&quot;:
if(ASPxClientEdit.ValidateGroup('Policies')==true){
cpAdd.PerformCallback('Delete');
}
else{
return false;
}
break;
case &quot;mnuEdit&quot;:
if(ASPxClientEdit.ValidateGroup('Policies')==true){
cpAdd.PerformCallback('Edit');
}
else{
return false;
}
break;
case &quot;mnuExit&quot;:
if (confirm(&quot;Do you want to exit?&quot;)){
        window.history.back();
                                       }
	break;
	default:
	break;
}	
}" />
                            <Items>
                                <dx:MenuItem Name="mnuAdd" Text="Save" NavigateUrl="javascript:void(0)" AdaptivePriority="1">
                                    <Image Url="~/Images/save.png"></Image>
                                </dx:MenuItem>
                                <dx:MenuItem Name="mnuEdit" Text="Edit" NavigateUrl="javascript:void(0)" AdaptivePriority="1">
                                    <Image Url="~/Images/edit.png"></Image>
                                </dx:MenuItem>
                                <dx:MenuItem Name="mnuDelete" Text="Delete" NavigateUrl="javascript:void(0)" AdaptivePriority="1">
                                    <Image Url="~/Images/delete.png"></Image>
                                </dx:MenuItem>
                                <dx:MenuItem Name="mnuExit" Text="Exit" NavigateUrl="javascript:void(0)" AdaptivePriority="1">
                                    <Image Url="~/Images/close.png"></Image>
                                </dx:MenuItem>
                            </Items>
                        </dx:ASPxMenu>
                    </div>
                </dx:PanelContent>
            </PanelCollection>
        </dx:ASPxPanel>
        <dx:ASPxCallbackPanel runat="server" ID="cpAdd" ClientInstanceName="cpAdd" OnCallback="cpAdd_Callback">
            <ClientSideEvents EndCallback="function(s, e) {
                if(s.cpResult!=null &amp;&amp; s.cpResult!='' ){
                alert(s.cpResult);
                }
                }" />
            <PanelCollection>
                <dx:PanelContent>
                    <dx:ASPxCallbackPanel runat="server" ID="cpSelect" ClientInstanceName="cpSelect" OnCallback="cpSelect_Callback">
                        <ClientSideEvents EndCallback="function(s, e) {
                if(s.cpResult!=null &amp;&amp; s.cpResult!='' ){
                alert(s.cpResult);
                }
                }" />
                        <PanelCollection>
                            <dx:PanelContent>
                                <div>
                                    <table class="auto-style1">
                                        <tr>
                                            <td>
                                                <dx:ASPxCallbackPanel runat="server" ID="cpDates" ClientInstanceName="cpDates" OnCallback="cpDates_Callback">
                                                    <PanelCollection>
                                                        <dx:PanelContent>
                                                            <dx:ASPxFormLayout ID="ASPxFormLayout4" runat="server" ColCount="2" EnableTheming="True" Theme="Aqua" Width="100%">
                                                                <SettingsAdaptivity AdaptivityMode="SingleColumnWindowLimit" SwitchToSingleColumnAtWindowInnerWidth="600" />
                                                                <Items>
                                                                    <dx:LayoutGroup ColCount="2" Caption="Policy Details" Width="100%">
                                                                        <Paddings PaddingTop="0px" PaddingLeft="0px" PaddingRight="0px" PaddingBottom="0px"></Paddings>
                                                                        <GroupBoxStyle>
                                                                            <Caption Font-Bold="true" Font-Size="12" />
                                                                        </GroupBoxStyle>
                                                                        <Items>

                                                                            <dx:LayoutItem Caption="Client" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxGridLookup ID="glClientNo" runat="server" AutoGenerateColumns="False" ClientInstanceName="glClientNo" DataSourceID="dsClients" Theme="Aqua" Width="100%" KeyFieldName="ClientNo">
                                                                                            <GridViewProperties>
                                                                                                <SettingsBehavior AllowFocusedRow="True" AllowSelectSingleRowOnly="True" />
                                                                                                <Settings ShowFilterRow="True" ShowFilterRowMenu="True" />
                                                                                            </GridViewProperties>
                                                                                            <Columns>
                                                                                                <dx:GridViewDataTextColumn FieldName="ClientNo" ShowInCustomizationForm="True" VisibleIndex="0">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="ClientName" ShowInCustomizationForm="True" VisibleIndex="1">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataDateColumn FieldName="DOB" ShowInCustomizationForm="True" VisibleIndex="2">
                                                                                                </dx:GridViewDataDateColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="AgeNxtBD" ShowInCustomizationForm="True" VisibleIndex="3">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                            </Columns>
                                                                                            <ClientSideEvents ValueChanged="function(s, e) {
cpComputeAge.PerformCallback();	
	
}" />
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Client is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxGridLookup>
                                                                                        <asp:SqlDataSource ID="dsClients" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="spGetClientsInfo"></asp:SqlDataSource>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="AgentNo" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxGridLookup ID="glIntermediaryNo" runat="server" AutoGenerateColumns="False" ClientInstanceName="glIntermediaryNo" DataSourceID="dsIntermediaries" Theme="Aqua" Width="100%" KeyFieldName="IntermediaryNo">
                                                                                            <GridViewProperties>
                                                                                                <SettingsBehavior AllowFocusedRow="True" AllowSelectSingleRowOnly="True" />
                                                                                                <Settings ShowFilterRow="True" ShowFilterRowMenu="True" />
                                                                                            </GridViewProperties>
                                                                                            <Columns>
                                                                                                <dx:GridViewDataTextColumn FieldName="IntermediaryNo" ShowInCustomizationForm="True" VisibleIndex="0">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="IntermediaryName" ShowInCustomizationForm="True" VisibleIndex="1">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                            </Columns>
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Customers">
                                                                                                <RequiredField ErrorText="Agent No is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxGridLookup>
                                                                                        <asp:SqlDataSource ID="dsIntermediaries" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="SELECT [IntermediaryNo], [IntermediaryName] FROM [Intermediaries] ORDER BY UpdatedDate desc ">
                                                                                            <SelectParameters>
                                                                                                <asp:Parameter DefaultValue="Intermediaries" Name="IntermediaryNo" Type="String" />
                                                                                            </SelectParameters>
                                                                                        </asp:SqlDataSource>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Life Assured" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtLifeAssured" runat="server" Width="100%" ClientInstanceName="txtAge" Theme="Aqua" Font-Bold="True">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Life Assured is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Life Assured IDNo" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtLifeAssuredIDNo" runat="server" Width="100%" ClientInstanceName="txtLifeAssuredIDNo" Theme="Aqua" Font-Bold="True">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Life Assured IDNo" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Assured Relationship" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxGridLookup ID="glRelationship" runat="server" AutoGenerateColumns="False" ClientInstanceName="glRelationship" DataSourceID="dsRelationship" Theme="Aqua" Width="100%" KeyFieldName="Code">
                                                                                            <GridViewProperties>
                                                                                                <SettingsBehavior AllowFocusedRow="True" AllowSelectSingleRowOnly="True" />
                                                                                                <Settings ShowFilterRow="True" ShowFilterRowMenu="True" />
                                                                                            </GridViewProperties>
                                                                                            <Columns>
                                                                                                <dx:GridViewDataTextColumn FieldName="Code" ShowInCustomizationForm="True" VisibleIndex="0">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="Description" ShowInCustomizationForm="True" VisibleIndex="1">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                            </Columns>
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Beneficiaries">
                                                                                                <RequiredField ErrorText="Relationship is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxGridLookup>
                                                                                        <asp:SqlDataSource ID="dsRelationship" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="SELECT [Code], [Description] FROM [UDCs] WHERE ([Category] = @Category) ORDER BY [UDCID] DESC">
                                                                                            <SelectParameters>
                                                                                                <asp:Parameter DefaultValue="Relationships" Name="Category" Type="String" />
                                                                                            </SelectParameters>
                                                                                        </asp:SqlDataSource>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Policy No" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtPolicyNo" runat="server" Width="100%" ClientInstanceName="txtPolicyNo" Theme="Aqua" Font-Bold="True">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Policy No is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Product" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxGridLookup ID="glProduct" runat="server" AutoGenerateColumns="False" ClientInstanceName="glProduct" DataSourceID="dsProducts" Theme="Aqua" Width="100%" KeyFieldName="ProductNo">
                                                                                            <GridViewProperties>
                                                                                                <SettingsBehavior AllowFocusedRow="True" AllowSelectSingleRowOnly="True" />
                                                                                                <Settings ShowFilterRow="True" ShowFilterRowMenu="True" />
                                                                                            </GridViewProperties>
                                                                                            <Columns>
                                                                                                <dx:GridViewDataTextColumn FieldName="ProductNo" ShowInCustomizationForm="True" VisibleIndex="0">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="ProductName" ShowInCustomizationForm="True" VisibleIndex="1">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="AssumedGrowthRate" ShowInCustomizationForm="True" VisibleIndex="2">
                                                                                                </dx:GridViewDataTextColumn>

                                                                                            </Columns>
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Product is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxGridLookup>
                                                                                        <asp:SqlDataSource ID="dsProducts" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="spGetProducts"></asp:SqlDataSource>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Policy Term (Years)" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxComboBox ID="txtPolicyTerm" runat="server" Width="100%" ClientInstanceName="txtPolicyTerm" Theme="Aqua" Font-Bold="True">

                                                                                            <Items>
                                                                                                <dx:ListEditItem Text="1" Value="1" />
                                                                                                <dx:ListEditItem Text="2" Value="2" />
                                                                                                <dx:ListEditItem Text="3" Value="3" />
                                                                                                <dx:ListEditItem Text="4" Value="4" />
                                                                                                <dx:ListEditItem Text="5" Value="5" />
                                                                                                <dx:ListEditItem Text="6" Value="6" />
                                                                                                <dx:ListEditItem Text="7" Value="7" />
                                                                                                <dx:ListEditItem Text="8" Value="8" />
                                                                                                <dx:ListEditItem Text="9" Value="9" />
                                                                                                <dx:ListEditItem Text="10" Value="10" />
                                                                                                <dx:ListEditItem Text="11" Value="11" />
                                                                                                <dx:ListEditItem Text="12" Value="12" />
                                                                                                <dx:ListEditItem Text="13" Value="13" />
                                                                                                <dx:ListEditItem Text="14" Value="14" />
                                                                                                <dx:ListEditItem Text="15" Value="15" />
                                                                                                <dx:ListEditItem Text="16" Value="16" />
                                                                                                <dx:ListEditItem Text="17" Value="17" />
                                                                                                <dx:ListEditItem Text="18" Value="18" />
                                                                                                <dx:ListEditItem Text="19" Value="19" />
                                                                                                <dx:ListEditItem Text="20" Value="20" />
                                                                                            </Items>
                                                                                            <ClientSideEvents ValueChanged="function(s, e) {
cpDates.PerformCallback();	
	
}" />
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Policy Term is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxComboBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Commencement Date" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxDateEdit ID="dtpCommencementDate" runat="server" Width="100%" ClientInstanceName="dtpCommencementDate" Theme="Aqua">
                                                                                            <ClientSideEvents DateChanged="function(s, e) {
cpDates.PerformCallback();	
	
}" />
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Commencement date is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxDateEdit>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>
                                                                            <dx:LayoutItem Caption="Last Premium Date" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxDateEdit ID="dtpLastPremiumDate" runat="server" Width="100%" ClientInstanceName="dtpLastPremiumDate" Theme="Aqua">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Last Premium date is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxDateEdit>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Maturity Date" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxDateEdit ID="dtpMaturityDate" runat="server" Width="100%" ClientInstanceName="dtpMaturityDate" Theme="Aqua">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Maturity date is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxDateEdit>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Premium" RequiredMarkDisplayMode="Required" CaptionStyle-ForeColor="Red" CaptionStyle-Font-Bold="true">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtTargetPremium" runat="server" Width="100%" ClientInstanceName="txtTargetPremium" Theme="Aqua" Font-Bold="True" ForeColor="Red">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Target premium is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                                <CaptionStyle Font-Bold="True" ForeColor="Red"></CaptionStyle>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Payment Frequency" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxGridLookup ID="glPaymentFrequency" runat="server" AutoGenerateColumns="False" ClientInstanceName="glPaymentFrequency" DataSourceID="dsPaymentFrequency" Theme="Aqua" Width="100%" KeyFieldName="Code">
                                                                                            <GridViewProperties>
                                                                                                <SettingsBehavior AllowFocusedRow="True" AllowSelectSingleRowOnly="True" />
                                                                                                <Settings ShowFilterRow="True" ShowFilterRowMenu="True" />
                                                                                            </GridViewProperties>
                                                                                            <Columns>
                                                                                                <dx:GridViewDataTextColumn FieldName="Code" ShowInCustomizationForm="True" VisibleIndex="0">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                                <dx:GridViewDataTextColumn FieldName="Description" ShowInCustomizationForm="True" VisibleIndex="1">
                                                                                                </dx:GridViewDataTextColumn>
                                                                                            </Columns>
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Payment frequency is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxGridLookup>
                                                                                        <asp:SqlDataSource ID="dsPaymentFrequency" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="SELECT [Code], [Description] FROM [UDCs] WHERE ([Category] = @Category)">
                                                                                            <SelectParameters>
                                                                                                <asp:Parameter DefaultValue="PayFrequency" Name="Category" Type="String" />
                                                                                            </SelectParameters>
                                                                                        </asp:SqlDataSource>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Sum Assured" RequiredMarkDisplayMode="Required" CaptionStyle-ForeColor="Red" CaptionStyle-Font-Bold="true">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtTargetAmount" runat="server" Width="100%" ClientInstanceName="txtTargetAmount" Theme="Aqua" Font-Bold="True" ForeColor="Red">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Target amount is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                                <CaptionStyle Font-Bold="True" ForeColor="Red"></CaptionStyle>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Alternative Policy No" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxTextBox ID="txtRefNo" runat="server" Width="100%" ClientInstanceName="txtRefNo" Theme="Aqua">
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Alternative Policy No is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxTextBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                            </dx:LayoutItem>

                                                                            <dx:LayoutItem Caption="Policy Status" RequiredMarkDisplayMode="Required">
                                                                                <LayoutItemNestedControlCollection>
                                                                                    <dx:LayoutItemNestedControlContainer runat="server">
                                                                                        <dx:ASPxComboBox ID="txtPolicyStatus" runat="server" Width="100%" ClientInstanceName="txtPolicyStatus" Theme="Aqua" Font-Bold="True">
                                                                                            <Items>
                                                                                                <dx:ListEditItem Text="AWAITING PREMIUM" Value="AWP" />
                                                                                                <dx:ListEditItem Text="AWAITING DOCUMENTS" Value="AWD" />
                                                                                                <dx:ListEditItem Text="NOT TAKEN UP" Value="NTU" />
                                                                                            </Items>
                                                                                            <ValidationSettings CausesValidation="True" Display="Dynamic" ErrorDisplayMode="Text" ValidationGroup="Policies">
                                                                                                <RequiredField ErrorText="Policy Status is required" IsRequired="True" />
                                                                                            </ValidationSettings>
                                                                                        </dx:ASPxComboBox>
                                                                                    </dx:LayoutItemNestedControlContainer>
                                                                                </LayoutItemNestedControlCollection>
                                                                                <CaptionCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </CaptionCellStyle>
                                                                                <NestedControlCellStyle>
                                                                                    <Paddings PaddingLeft="0px" />
                                                                                </NestedControlCellStyle>
                                                                            </dx:LayoutItem>
                                                                        </Items>
                                                                    </dx:LayoutGroup>
                                                                </Items>
                                                                <SettingsItemCaptions Location="Left" />
                                                            </dx:ASPxFormLayout>
                                                        </dx:PanelContent>
                                                    </PanelCollection>
                                                </dx:ASPxCallbackPanel>
                                            </td>
                                        </tr>
                                    </table>

                                </div>

                                <dx:ASPxGridView runat="server" Width="100%" ID="GvPolicies" ClientInstanceName="GvPolicies" EnableTheming="True" Theme="Aqua" KeyFieldName="PolicyNo;ProductNo" OnFillContextMenuItems="Grid_FillContextMenuItems" OnContextMenuItemClick="Grid_ContextMenuItemClick" AutoGenerateColumns="False" DataSourceID="SqlDataSource1" OnCustomCallback="GvPolicies_CustomCallback">
                                    <Settings VerticalScrollBarMode="Visible" ShowFilterBar="Visible" ShowFooter="true" ShowFilterRow="True" ShowFilterRowMenu="True" ShowGroupPanel="True" />
                                    <SettingsBehavior AllowSelectByRowClick="True" ColumnResizeMode="NextColumn" />
                                    <SettingsDataSecurity AllowDelete="False" AllowEdit="False" AllowInsert="False" />
                                    <EditFormLayoutProperties>
                                        <SettingsAdaptivity AdaptivityMode="SingleColumnWindowLimit" SwitchToSingleColumnAtWindowInnerWidth="600" />
                                    </EditFormLayoutProperties>
                                    <ClientSideEvents ContextMenuItemClick="function(s, e) {
OnContextMenuItemClick(s, e);	
}"
                                        EndCallback="function(s, e) {
if( s.cpResult!=null &amp;&amp;  s.cpResult!=' '){
 alert( s.cpResult);
}	
}"
                                        RowClick="function(s, e) {
GvPolicies.PerformCallback(e.visibleIndex);
 setTimeout(function(){		
			cpSelect.PerformCallback();

},500);	
}" />
                                    <SettingsContextMenu Enabled="True">
                                    </SettingsContextMenu>
                                    <SettingsPager NumericButtonCount="6" />
                                    <Columns>
                                        <dx:GridViewDataTextColumn FieldName="ClientNo" ReadOnly="True" VisibleIndex="0">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="ClientName" ReadOnly="True" VisibleIndex="1">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="LifeAssured" ReadOnly="True" VisibleIndex="2">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="PolicyNo" ReadOnly="True" VisibleIndex="3">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataDateColumn FieldName="CommenceDate" ReadOnly="True" VisibleIndex="4">
                                        </dx:GridViewDataDateColumn>
                                        <dx:GridViewDataDateColumn FieldName="LastPremiumDate" ReadOnly="True" VisibleIndex="5">
                                        </dx:GridViewDataDateColumn>
                                        <dx:GridViewDataDateColumn FieldName="MaturityDate" ReadOnly="True" VisibleIndex="6">
                                        </dx:GridViewDataDateColumn>
                                        <dx:GridViewDataTextColumn FieldName="ProductNo" ReadOnly="True" VisibleIndex="7">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="ProductName" ReadOnly="True" VisibleIndex="8">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="PolicyTerm" ReadOnly="True" VisibleIndex="9">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="SumAssured" ReadOnly="True" VisibleIndex="10">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="PremiumAmount" ReadOnly="True" VisibleIndex="11">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="PolicyStatus" ReadOnly="True" VisibleIndex="12">
                                        </dx:GridViewDataTextColumn>
                                        <dx:GridViewDataTextColumn FieldName="CreatedBy" ReadOnly="True" VisibleIndex="13">
                                        </dx:GridViewDataTextColumn>
                                    </Columns>

                                    <Styles>
                                        <Cell Wrap="False"></Cell>
                                    </Styles>
                                </dx:ASPxGridView>
                                <script type="text/javascript">
                                    function OnContextMenuItemClick(sender, args) {

                                        if (args.item.name == "ExportToPDF" || args.item.name == "ExportToXLS") {
                                            args.processOnServer = true;
                                            args.usePostBack = true;
                                        }
                                        else if (args.item.name == "SumSelected") {
                                            args.processOnServer = true;
                                        }
                                    }
                                </script>
                            </dx:PanelContent>
                        </PanelCollection>
                    </dx:ASPxCallbackPanel>
                </dx:PanelContent>
            </PanelCollection>
        </dx:ASPxCallbackPanel>
        <script type="text/javascript">
        </script>
        <dx:ASPxGridViewExporter ID="ASPxGridViewExporter1" runat="server" GridViewID="GvPolicies">
        </dx:ASPxGridViewExporter>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:imsconn %>" SelectCommand="spGetPoliciesNoQuotes"></asp:SqlDataSource>
    </form>
</body>
</html>

