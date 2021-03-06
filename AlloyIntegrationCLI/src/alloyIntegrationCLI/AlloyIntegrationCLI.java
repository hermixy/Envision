package alloyIntegrationCLI;

import java.io.File;
import java.io.IOException;

import edu.mit.csail.sdg.alloy4.A4Reporter;
import edu.mit.csail.sdg.alloy4.Err;
import edu.mit.csail.sdg.alloy4compiler.ast.Command;
import edu.mit.csail.sdg.alloy4compiler.ast.Module;
import edu.mit.csail.sdg.alloy4compiler.parser.CompUtil;
import edu.mit.csail.sdg.alloy4compiler.translator.A4Options;
import edu.mit.csail.sdg.alloy4compiler.translator.A4Solution;
import edu.mit.csail.sdg.alloy4compiler.translator.TranslateAlloyToKodkod;
import edu.mit.csail.sdg.alloy4viz.StaticInstanceReader;
import edu.mit.csail.sdg.alloy4viz.AlloyInstance;
import edu.mit.csail.sdg.alloy4viz.VizGraphPanel;
import edu.mit.csail.sdg.alloy4viz.VizState;

public class AlloyIntegrationCLI
{
	public static void main(String[] args) throws Err, IOException
	{
		//argument 1: The path to the file with the model
		//argument 2: The path to the desired output directory
		//argument 3: The maximum number of images that should be generated
		if (args.length < 3)
			return;
		String modelPath = args[0];
		String outputPath = args[1];
		int maxImages = Integer.parseInt(args[2]);
		
		A4Reporter rep = new A4Reporter();
		Module world = CompUtil.parseEverything_fromFile(rep, null, modelPath);
		A4Options opt = new A4Options();
		opt.solver = A4Options.SatSolver.SAT4J;
		opt.unrolls = 3;
		Command cmd = world.getAllCommands().get(0);
		A4Solution sol = TranslateAlloyToKodkod.execute_command(rep, world.getAllReachableSigs(), cmd, opt);
		
		int i = 0;
		while (sol.satisfiable() && i < maxImages)
		{
			sol.writeXML(outputPath + "sol.xml");
			AlloyInstance anAlloyInstance = StaticInstanceReader.parseInstance(new File(outputPath + "sol.xml"));
			
			VizGraphPanel aVizGraphPanel = new VizGraphPanel(new VizState(anAlloyInstance),false);
			aVizGraphPanel.alloyGetViewer().alloySaveAsPNG(outputPath + "image" + (i++) + ".png", 1, 0, 0);
			
			sol = sol.next();
		}
	}

}
