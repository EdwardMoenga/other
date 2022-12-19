using DevExpress.Web;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Reflection;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Investment_PolicyMasterNoQuote2 : System.Web.UI.Page
{
    DataSet ds = new DataSet();
    DataSet dsRights = new DataSet();
    Security _Security = new Security();
    Policy _Policy = new Policy();
    protected void Page_Load(object sender, EventArgs e)
    {
        try
        {
            if (!(HttpContext.Current.Request.Cookies["UserName"].Value.ToString().Equals(string.Empty) || HttpContext.Current.Request.Cookies["UserName"].Value.Equals(null)))
            {
                _Security.SecurityModule = "Policies";
                dsRights = _Security.GetUserRights();
                if (dsRights.Tables["UserRoles"].Rows[0]["View"].Equals(true))
                {
                    if (this.Page.IsPostBack.Equals(false))
                    {
                        txtTargetAmount.Text = "";
                        txtTargetPremium.Text = "";
                        dtpLastPremiumDate.ReadOnly = true;
                        dtpMaturityDate.ReadOnly = true;
                        txtPolicyTerm.SelectedIndex = 4;
                        txtLifeAssured.Text = "Self";
                        txtLifeAssuredIDNo.Text = "0";
                        glRelationship.Value = "None";
                        txtPolicyStatus.Value = "AWP";
                    }
                    SelectPolicyDates();
                }
                else
                {
                    Response.Redirect("Login.aspx");
                }
            }
            else
            {
                Response.Redirect("Login.aspx");
            }
        }
        catch (Exception ex)
        {
            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "Initializing loading policies page";
            _Security.SaveError();
        }
    }
    protected void Grid_FillContextMenuItems(object sender, ASPxGridViewContextMenuEventArgs e)
    {
        try
        {
            if (e.MenuType == GridViewContextMenuType.Rows)
            {
                var item = e.CreateItem("Export", "Export");
                item.BeginGroup = true;
                e.Items.Insert(e.Items.IndexOfCommand(GridViewContextMenuCommand.Refresh), item);

                AddMenuSubItem(item, "pdf", "ExportToPDF", @"/Images/pdf1.png", true);
                AddMenuSubItem(item, "excel", "ExportToXLS", @"/Images/xcel3.png", true);
            }
        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "Policy context menu";
            _Security.SaveError();
        }

    }


    private static void AddMenuSubItem(GridViewContextMenuItem parentItem, string text, string name, string imageUrl, bool isPostBack)
    {
        try
        {
            var exportToXlsItem = parentItem.Items.Add(text, name);
            exportToXlsItem.Image.Url = imageUrl;
        }
        catch (Exception ex)
        {
            var _Security = new Security();
            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "Adding item on policy context menu";
            _Security.SaveError();
        }

    }
    protected void Grid_ContextMenuItemClick(object sender, ASPxGridViewContextMenuItemClickEventArgs e)
    {
        try
        {
            if (dsRights.Tables["UserRoles"].Rows[0]["Export"].Equals(true))
            {
                switch (e.Item.Name)
                {
                    case "ExportToPDF":
                        ASPxGridViewExporter1.WritePdfToResponse();
                        break;
                    case "ExportToXLS":
                        ASPxGridViewExporter1.WriteXlsToResponse();
                        break;
                }
            }
            else
            {
                GvPolicies.JSProperties["cpResult"] = "No right to export policy";
            }
        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "Exporting policy details";
            _Security.SaveError();
        }
    }

    public void SelectPolicyDates()
    {
        try
        {
            _Policy.CommenceDate = dtpCommencementDate.Date;
            _Policy.PolicyTerm = Convert.ToInt32(txtPolicyTerm.Text);
            ds = _Policy.SelectPolicyDates();
            dtpLastPremiumDate.Date = Convert.ToDateTime(ds.Tables["Policies"].Rows[0]["LastPremDate"].ToString());
            dtpMaturityDate.Date = Convert.ToDateTime(ds.Tables["Policies"].Rows[0]["MaturityDate"].ToString());
        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "selecting policy dates";
            _Security.SaveError();
        }
    }
    
    private void ClearField()
    {
        glClientNo.Value = "";
        txtLifeAssured.Text = "Self";
        txtLifeAssuredIDNo.Text = "0";
        glRelationship.Value = "None";
        txtPolicyNo.Text = "";
        glProduct.Value = "";
        glPaymentFrequency.Value = "";
        txtTargetAmount.Text = "";
        txtTargetPremium.Text = "";
        txtPolicyTerm.Text = "";
        dtpCommencementDate.Date = DateTime.Now;
        dtpLastPremiumDate.Date = DateTime.Now;
        dtpMaturityDate.Date = DateTime.Now;
        txtPolicyTerm.SelectedIndex = 4;
        txtPolicyStatus.Value = "AWP";
        glIntermediaryNo.Value = "";
    }
    private void DisableField()
    {
        glClientNo.ClientEnabled = false;
        txtLifeAssuredIDNo.ClientEnabled = false;
        glRelationship.ClientEnabled = false;
        txtPolicyNo.ClientEnabled = false;
        glProduct.ClientEnabled = false;
        glPaymentFrequency.ClientEnabled = false;
        txtTargetAmount.ClientEnabled = false;
        txtTargetPremium.ClientEnabled = false;
        txtLifeAssured.ClientEnabled = false;
        txtPolicyTerm.ClientEnabled = false;
        dtpMaturityDate.ClientEnabled = false;
        txtPolicyTerm.ClientEnabled = false;
        txtPolicyStatus.ClientEnabled = false;
        glIntermediaryNo.ClientEnabled = false;
    }
    private void EnableField()
    {
        glClientNo.ClientEnabled = true;
        txtLifeAssuredIDNo.ClientEnabled = true;
        glRelationship.ClientEnabled = true;
        txtPolicyNo.ClientEnabled = true;
        glProduct.ClientEnabled = true;
        glPaymentFrequency.ClientEnabled = true;
        txtTargetAmount.ClientEnabled = true;
        txtTargetPremium.ClientEnabled = true;
        txtLifeAssured.ClientEnabled = true;
        txtPolicyTerm.ClientEnabled = true;
        dtpMaturityDate.ClientEnabled = true;
        txtPolicyTerm.ClientEnabled = true;
        txtPolicyStatus.ClientEnabled = true;
        glIntermediaryNo.ClientEnabled = true;
    }

    protected void cpAdd_Callback(object sender, DevExpress.Web.CallbackEventArgsBase e)
    {
        try
        {
            cpAdd.JSProperties["cpResult"] = "";
            switch (e.Parameter)
            {

                case "Add":
                    if (dsRights.Tables["UserRoles"].Rows[0]["Add"].Equals(true))
                    {
                      //Convert.ToString(this.glClientNo.GridView.GetRowValues(glClientNo.GridView.FocusedRowIndex, new String[] { "IntermediaryNo" }));
                        _Policy.ClientNo = glClientNo.Value.ToString();
                        _Policy.IntermediaryNo = glIntermediaryNo.Value.ToString();
                        _Policy.LifeAssured = txtLifeAssured.Text;
                        _Policy.AssuredIDNo = txtLifeAssuredIDNo.Text;
                        _Policy.AssuredRelshp = glRelationship.Value.ToString();
                        _Policy.DOB = Convert.ToDateTime(this.glClientNo.GridView.GetRowValues(glClientNo.GridView.FocusedRowIndex, new String[] { "DOB" }));
                        _Policy.PolicyNo = txtPolicyNo.Text;
                        _Policy.QuoteNo = "0";
                        _Policy.ProductNo = glProduct.Value.ToString();
                        _Policy.ProductName = Convert.ToString(this.glProduct.GridView.GetRowValues(glProduct.GridView.FocusedRowIndex, new String[] { "ProductName" }));
                        _Policy.CommenceDate = dtpCommencementDate.Date;
                        _Policy.PolicyTerm =Convert.ToInt32(txtPolicyTerm.Value);
                        _Policy.LastPremiumDate = dtpLastPremiumDate.Date;
                        _Policy.MaturityDate = dtpMaturityDate.Date;
                        _Policy.PaymentFrequency = glPaymentFrequency.Value.ToString();
                        _Policy.AssumedInterestRate = Convert.ToSingle(this.glProduct.GridView.GetRowValues(glProduct.GridView.FocusedRowIndex, new String[] { "AssumedGrowthRate" }));
                        _Policy.TargetAmount = Convert.ToDecimal(txtTargetAmount.Text);
                        _Policy.TargetPremium = Convert.ToDecimal(txtTargetPremium.Text);
                        _Policy.AlternateRefNo = txtRefNo.Text;
                        _Policy.PolicyStatus = txtPolicyStatus.Value.ToString();
                        if (_Policy.SavePoliciesNoQuote())
                        {
                            cpAdd.JSProperties["cpResult"] = "Policy added successfully";
                            ClearField();
                        }
                        else
                        {
                            cpAdd.JSProperties["cpResult"] = "Policy failed to add";
                        }
                        
                       GvPolicies.DataBind();
                    }
                    else
                    {
                        cpAdd.JSProperties["cpResult"] = "No right to add policy";
                    }
                    break;
                case "Delete":
                    if (dsRights.Tables["UserRoles"].Rows[0]["Delete"].Equals(true))
                    {
                        _Policy.PolicyNo = txtPolicyNo.Text;
                        if (_Policy.DeletePolicyNoQuote())
                        {
                            cpAdd.JSProperties["cpResult"] = "Policy deleted successfully";
                            ClearField();
                        }
                        else
                        {
                            cpAdd.JSProperties["cpResult"] = "Policy deletion failed";
                        }
                        GvPolicies.DataBind();
                    }
                    else
                    {
                        cpAdd.JSProperties["cpResult"] = "No right to delete policy";
                    }
                    break;
                case "Edit":
                    if (dsRights.Tables["UserRoles"].Rows[0]["Edit"].Equals(true))
                    {
                        EnableField();
                    }
                    else
                    {
                        cpAdd.JSProperties["cpResult"] = "No right to edit policy";
                    }
                    break;
                default:
                    break;
            }


        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "performing callback on form policy";
            _Security.SaveError();
        }
    }

    protected void cpDates_Callback(object sender, DevExpress.Web.CallbackEventArgsBase e)
    {
        try
        {
            SelectPolicyDates();

        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "performing callback on form policy";
            _Security.SaveError();
        }
    }

    protected void cpSelect_Callback(object sender, DevExpress.Web.CallbackEventArgsBase e)
    {
        try
        {
            _Policy.PolicyNo = Session["PolicyNo"].ToString();
            _Policy.ProductNo = Session["ProductNo"].ToString();
            ds = _Policy.SelectPolicy();
            if (ds.Tables["Policies"].Rows.Count > 0)
            {
                DisableField();
                glClientNo.Value = ds.Tables["Policies"].Rows[0]["ClientNo"].ToString();
                glIntermediaryNo.Value = ds.Tables["Policies"].Rows[0]["IntermediaryNo"].ToString();
                txtLifeAssured.Text = ds.Tables["Policies"].Rows[0]["LifeAssured"].ToString();
                txtLifeAssuredIDNo.Text = ds.Tables["Policies"].Rows[0]["AssuredIDNo"].ToString();
                glRelationship.Value = ds.Tables["Policies"].Rows[0]["AssuredRelshp"].ToString();
                txtPolicyNo.Text = ds.Tables["Policies"].Rows[0]["PolicyNo"].ToString();
                glProduct.Value = ds.Tables["Policies"].Rows[0]["ProductNo"].ToString();
                dtpCommencementDate.Date = Convert.ToDateTime(ds.Tables["Policies"].Rows[0]["CommenceDate"].ToString());
                txtPolicyTerm.Text = ds.Tables["Policies"].Rows[0]["PolicyTerm"].ToString();
                dtpLastPremiumDate.Date = Convert.ToDateTime(ds.Tables["Policies"].Rows[0]["LastPremiumDate"].ToString());
                dtpMaturityDate.Date = Convert.ToDateTime(ds.Tables["Policies"].Rows[0]["MaturityDate"].ToString());
                glPaymentFrequency.Value = ds.Tables["Policies"].Rows[0]["PaymentFrequency"].ToString();
                txtTargetAmount.Text = ds.Tables["Policies"].Rows[0]["SumAssured"].ToString();
                txtTargetPremium.Text = ds.Tables["Policies"].Rows[0]["PremiumAmount"].ToString();

                txtPolicyStatus.Value = ds.Tables["Policies"].Rows[0]["PolicyStatus"].ToString();
            }
        }
        catch (Exception ex)
        {

            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "performing callback on form policy";
            _Security.SaveError();
        }
    }
    protected void GvPolicies_CustomCallback(object sender, ASPxGridViewCustomCallbackEventArgs e)
    {
        try
        {
            object PolicyNo = GvPolicies.GetRowValues(Convert.ToInt32(e.Parameters), "PolicyNo");
            object ProductNo = GvPolicies.GetRowValues(Convert.ToInt32(e.Parameters), "ProductNo");
            Session["PolicyNo"] = PolicyNo;
            Session["ProductNo"] = ProductNo;
        }
        catch (Exception ex)
        {
            _Security.ErrorDesscription = ex.Message;
            _Security.ErrorModule = "performing custom callback on form policies";
            _Security.SaveError();
        }
    }
}